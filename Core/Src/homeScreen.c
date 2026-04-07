#include "homeScreen.h"
#include "plantProfiles.h"
#include "src/core/lv_obj_pos.h"
#include "src/core/lv_obj_style_gen.h"
#include "src/font/lv_font.h"
#include "src/misc/lv_area.h"
#include "src/widgets/label/lv_label.h"
#include <stdint.h>
#include <string.h>
#include "lights.h"

lv_obj_t *waterTempLabel = NULL;
lv_obj_t *enclosureTempLabel = NULL;
lv_obj_t *waterLevelLabel = NULL;
lv_obj_t *pHLabel = NULL;
lv_obj_t *TDSLabel = NULL;

lv_obj_t *plantNameLabel = NULL;
lv_obj_t *plantStageLabel = NULL;
lv_obj_t *plantLightOnLabel = NULL;
lv_obj_t *plantRGBLabel = NULL;
lv_obj_t *plantDurationLabel = NULL;
lv_obj_t *growingDaysLabel = NULL;

uint32_t growthDays = 0;

void drawHomeScreen(lv_obj_t *homeScreen) {
  lv_obj_set_style_text_font(homeScreen, &lv_font_montserrat_14, 0);
  /* Sensor Readings */
  int32_t y = 5;
  int32_t padding = 20;

  lv_obj_t *sensorLabel = lv_label_create(homeScreen);
  lv_obj_set_style_text_font(sensorLabel, &lv_font_montserrat_16, 0);
  lv_label_set_text(sensorLabel, "Sensor Readings");
  lv_obj_set_style_text_color(sensorLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(sensorLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += padding;

  waterTempLabel = lv_label_create(homeScreen);
  lv_label_set_text(waterTempLabel, "Water: __._ C");
  lv_obj_set_style_text_color(waterTempLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(waterTempLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += padding;

  enclosureTempLabel = lv_label_create(homeScreen);
  lv_label_set_text(enclosureTempLabel, "Encl: __._ C");
  lv_obj_set_style_text_color(enclosureTempLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(enclosureTempLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += padding;

  waterLevelLabel = lv_label_create(homeScreen);
  lv_label_set_text(waterLevelLabel, "Water Lvl: ___%");
  lv_obj_set_style_text_color(waterLevelLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(waterLevelLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += padding;

  pHLabel = lv_label_create(homeScreen);
  lv_label_set_text(pHLabel, "pH: __");
  lv_obj_set_style_text_color(pHLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(pHLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += padding;

  TDSLabel = lv_label_create(homeScreen);
  lv_label_set_text(TDSLabel, "TDS: __._ uS/cm");
  lv_obj_set_style_text_color(TDSLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(TDSLabel, LV_ALIGN_TOP_LEFT, 0, y);

  /* Plant Profile Information */
  y = 0;
  lv_obj_t *plantProfileLabel = lv_label_create(homeScreen);
  lv_obj_set_style_text_font(plantProfileLabel, &lv_font_montserrat_16, 0);
  lv_label_set_text(plantProfileLabel, "Plant Profile");
  lv_obj_set_style_text_color(plantProfileLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantProfileLabel, LV_ALIGN_TOP_RIGHT, 0, y);

  y += padding;
  plantNameLabel = lv_label_create(homeScreen);
  lv_label_set_text(plantNameLabel, "Plant: --");
  lv_obj_set_style_text_color(plantNameLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantNameLabel, LV_ALIGN_TOP_RIGHT, 0, y);

  y += padding;
  plantStageLabel = lv_label_create(homeScreen);
  lv_label_set_text(plantStageLabel, "Stage: --");
  lv_obj_set_style_text_color(plantStageLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantStageLabel, LV_ALIGN_TOP_RIGHT, 0, y);
  y += padding;

  plantLightOnLabel = lv_label_create(homeScreen);
  lv_label_set_text(plantLightOnLabel, "Light On: ---- min");
  lv_obj_set_style_text_color(plantLightOnLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantLightOnLabel, LV_ALIGN_TOP_RIGHT, 0, y);

  y += padding;
  plantRGBLabel = lv_label_create(homeScreen);
  lv_label_set_text(plantRGBLabel, "W/R/B: --/--/-- %");
  lv_obj_set_style_text_color(plantRGBLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantRGBLabel, LV_ALIGN_TOP_RIGHT, 0, y);

  y += padding;
  plantDurationLabel = lv_label_create(homeScreen);
  lv_label_set_text(plantDurationLabel, "Duration: --- days");
  lv_obj_set_style_text_color(plantDurationLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(plantDurationLabel, LV_ALIGN_TOP_RIGHT, 0, y);

  y += padding;
  growingDaysLabel = lv_label_create(homeScreen);
  lv_label_set_text(growingDaysLabel, "Day: ---");
  lv_obj_set_style_text_color(growingDaysLabel, lv_color_hex(0xFFFFFF), 0);
  lv_obj_align(growingDaysLabel, LV_ALIGN_TOP_RIGHT, 0, y);
}

void updatePlantProfileLabels(const struct plantProfile *p) {
  if (!p)
    return;

  lv_label_set_text_fmt(plantNameLabel, "Plant: %s", p->name);
  lv_label_set_text_fmt(plantStageLabel, "Stage: %s", getStageName(p->stage));

  lv_label_set_text_fmt(plantLightOnLabel, "Light On: %u min",
                        p->lightOnMinutes);
  lv_label_set_text_fmt(plantRGBLabel, "W/R/B/NIR: %u/%u/%u/%u %%",
                          p->whiteLightPercentage, p->redLightPercentage,
                          p->blueLightPercentage, p->nirLightPercentage);

  lv_label_set_text_fmt(plantDurationLabel, "Duration: %lu days",
                        (unsigned long)p->growthDurationDays);
  growthDays = 1;
  lv_label_set_text_fmt(growingDaysLabel, "Day: %lu",
                        (unsigned long)growthDays);
}

// Unused for now. Currently updating the text for each individual sensor.
// May use this when all sensors are finished
void updateSensorLabels(float waterTemp, float enclosureTemp,
                        uint8_t waterLevelPct, float pH, float TDS) {
  if (!waterTempLabel || !enclosureTempLabel || !waterLevelLabel || !pHLabel ||
      !TDSLabel) {
    return; // labels not created yet
  }

  lv_label_set_text_fmt(waterTempLabel, "Water: %.1f C", waterTemp);
  lv_label_set_text_fmt(enclosureTempLabel, "Encl: %.1f C", enclosureTemp);
  lv_label_set_text_fmt(waterLevelLabel, "Water Lvl: %u%%", waterLevelPct);
  lv_label_set_text_fmt(pHLabel, "pH: %.2f", pH);
  lv_label_set_text_fmt(TDSLabel, "TDS: %.0f ppm", TDS);
}
