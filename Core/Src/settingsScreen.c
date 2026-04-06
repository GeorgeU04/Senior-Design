#include "settingsScreen.h"
#include "DS18B20.h"
#include "TDS_Sensor_Driver.h"
#include "main.h"
#include "pH_Sensor_Driver.h"
#include "src/misc/lv_area.h"
#include "src/widgets/button/lv_button.h"
#include "src/widgets/label/lv_label.h"
#include "src/widgets/msgbox/lv_msgbox.h"
#include "src/widgets/switch/lv_switch.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t useFahrenheit = false;
lv_obj_t *temperatureUnitsLabel = NULL;

uint16_t systemStatus = 0;

/* 0000_0000_0000_0000 */
/* 0 is nominal
 * 1 is error
 * MSB->LSB
 * 0 -> not used
 * 0 -> not used
 * 0 -> not used
 * 0 -> not used
 * 0 -> not used
 * 0 -> not used
 * 0 -> not used
 * 0 -> fan3 status
 * 0 -> fan2 status
 * 0 -> fan1 status
 * 0 -> fan0 status
 * 0 -> water level sensor status
 * 0 -> TDS sensor status
 * 0 -> pH sensor status
 * 0 -> enclosure temp sensor status
 * 0 -> water temp sensor status
 */

static void setErrorText(char *text, size_t size) {
  text[0] = '\0';
  if (systemStatus == 0) {
    sniprintf(text, size, "All Systems Nominal");
    return;
  }

  if (systemStatus & (1 << WATER_TEMP))
    strncat(text, "Water Temp: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << ENCLOSURE_TEMP))
    strncat(text, "Enclosure Temp: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << PH_LEVEL))
    strncat(text, "pH: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << TDS_LEVEL))
    strncat(text, "ECS: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << WATER_LEVEL))
    strncat(text, "Water Level: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << FAN_0))
    strncat(text, "Fan 0: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << FAN_1))
    strncat(text, "Fan 1: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << FAN_2))
    strncat(text, "Fan 2: Error\n", (size - strlen(text)) - 1);
  if (systemStatus & (1 << FAN_3))
    strncat(text, "Fan 3: Error\n", (size - strlen(text)) - 1);
}

static void drawPopUp() {
  lv_obj_t *popUp = lv_msgbox_create(NULL);
  lv_msgbox_add_title(popUp, "System Diagnostic Results");
  char errorMsg[256];
  setErrorText(errorMsg, sizeof(errorMsg));
  lv_msgbox_add_text(popUp, errorMsg);
  lv_msgbox_add_close_button(popUp);
  lv_obj_set_width(popUp, 300);
  systemStatus = 0;
}

// only the temp sensors are checked for errors right now, others will be added
// later
void getSystemStatus() {

  /* Check temp sensors */
  float waterTemps[2] = {0};
  float enclosureTemps[2] = {0};
  float ECSVals[3] = {0};
  float pHVals[3] = {0};
  uint8_t waterTempInValid = 0;
  uint8_t enclosureTempInValid = 0;
  uint8_t i = 0;
  uint8_t j = 0;

  while (i < 2 && j < 2) {
    if (asyncTemperatureReading(devices.enclosureTempSensor,
                                &enclosureTemps[i])) {
      if (!devices.enclosureTempSensor->validReading)
        ++enclosureTempInValid;
      ++i;
    }
    if (asyncTemperatureReading(devices.waterTempSensor, &waterTemps[j])) {
      ++j;
      if (!devices.waterTempSensor->validReading)
        ++waterTempInValid;
    }
  }
  // the sensor returns 0 upon disconnect, if the actual value is 0 degrees C we
  // have bigger issues
  if (waterTempInValid == 2 ||
      (waterTemps[0] == 0.0f && waterTemps[1] == 0.0f)) {
    systemStatus |= 1 << WATER_TEMP;
  }
  if (enclosureTempInValid == 2 ||
      (enclosureTemps[0] == 0.0f && enclosureTemps[1] == 0.0f)) {
    systemStatus |= 1 << ENCLOSURE_TEMP;
  }
  i = 0;
  while (i < 3) {
    readTDS(devices.tds);
    ECSVals[i] = devices.tds->ECVal;
    readpH(devices.ph);
    pHVals[i++] = devices.ph->pHVal;
  }

  if (ECSVals[0] > 3 && ECSVals[1] > 3 && ECSVals[2] > 3) {
    systemStatus |= 1 << TDS_LEVEL;
  }

  if (pHVals[0] > 14 && pHVals[1] > 14 && pHVals[2] > 14) {
    systemStatus |= 1 << PH_LEVEL;
  }

  drawPopUp();
}

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  useFahrenheit = lv_obj_has_state(obj, LV_STATE_CHECKED);
  (void)obj;
  if (code == LV_EVENT_VALUE_CHANGED) {
    lv_label_set_text(temperatureUnitsLabel, useFahrenheit
                                                 ? "Temp Units: Fahrenheit"
                                                 : "Temp Units: Celsius");
  } else if (code == LV_EVENT_CLICKED) {
    getSystemStatus();
  }
}

void drawSettingsScreen(lv_obj_t *settingsScreen) {
  int32_t y = 5;
  int32_t padding = 20;
  temperatureUnitsLabel = lv_label_create(settingsScreen);
  lv_label_set_text(temperatureUnitsLabel, "Temp Units: Celsius");
  lv_obj_set_style_text_color(temperatureUnitsLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(temperatureUnitsLabel, LV_ALIGN_TOP_LEFT, 0, y);

  lv_obj_t *tempUnitsSwitch = lv_switch_create(settingsScreen);
  lv_obj_align(tempUnitsSwitch, LV_ALIGN_TOP_RIGHT, 0, y);

  lv_obj_add_event_cb(tempUnitsSwitch, event_handler, LV_EVENT_VALUE_CHANGED,
                      NULL);
  y += padding;

  lv_obj_t *systemCheckButton = lv_button_create(settingsScreen);
  lv_obj_t *systemCheckLabel = lv_label_create(systemCheckButton);
  lv_label_set_text(systemCheckLabel, "Perform System Check");
  lv_obj_set_style_text_color(systemCheckLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(systemCheckButton, LV_ALIGN_BOTTOM_MID, 0, -60);
  lv_obj_add_event_cb(systemCheckButton, event_handler, LV_EVENT_CLICKED, NULL);
}
