#include "settingsScreen.h"
#include "src/core/lv_obj.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_style.h"
#include "src/widgets/label/lv_label.h"
#include "src/widgets/switch/lv_switch.h"
#include <stdint.h>

uint8_t useFahrenheit = false;
lv_obj_t *temperatureUnitsLabel = NULL;

static void event_handler(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  useFahrenheit = lv_obj_has_state(obj, LV_STATE_CHECKED);
  (void)obj;
  if (code == LV_EVENT_VALUE_CHANGED) {
    lv_label_set_text(temperatureUnitsLabel, useFahrenheit
                                                 ? "Temp Units: Fahrenheit"
                                                 : "Temp Units: Celsius");
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
  lv_obj_align(tempUnitsSwitch, LV_ALIGN_TOP_RIGHT, 0, 0);

  lv_obj_add_event_cb(tempUnitsSwitch, event_handler, LV_EVENT_VALUE_CHANGED,
                      NULL);
  y += padding;
}
