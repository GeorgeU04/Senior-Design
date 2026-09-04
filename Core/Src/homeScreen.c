#include "homeScreen.h"
#include "guiTheme.h"
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

static lv_obj_t *createReadingRow(lv_obj_t *parent, const char *text) {
  lv_obj_t *label = lv_label_create(parent);
  lv_label_set_text(label, text);
  gui_style_body_text(label);
  /* Keep text inside the card; ellipsize if still too long */
  lv_obj_set_width(label, lv_pct(100));
  lv_label_set_long_mode(label, LV_LABEL_LONG_MODE_DOTS);
  return label;
}

void drawHomeScreen(lv_obj_t *homeScreen) {
  /* Fit within 240px height with navbar — no overflow / no scroll */
  lv_obj_t *sensorCard = gui_create_card(homeScreen, 152, 160);
  lv_obj_align(sensorCard, LV_ALIGN_TOP_LEFT, 0, 0);

  lv_obj_t *sensorTitle = lv_label_create(sensorCard);
  lv_label_set_text(sensorTitle, "Sensors");
  gui_style_section_title(sensorTitle);
  lv_obj_align(sensorTitle, LV_ALIGN_TOP_LEFT, 0, 0);

  int32_t y = 22;
  const int32_t rowGap = 20;

  waterTempLabel = createReadingRow(sensorCard, "Water: __._ C");
  lv_obj_align(waterTempLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  enclosureTempLabel = createReadingRow(sensorCard, "Encl: __._ C");
  lv_obj_align(enclosureTempLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  waterLevelLabel = createReadingRow(sensorCard, "Level: ____");
  lv_obj_align(waterLevelLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  pHLabel = createReadingRow(sensorCard, "pH: __");
  lv_obj_align(pHLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  TDSLabel = createReadingRow(sensorCard, "ECS: __._ mS/cm");
  lv_obj_align(TDSLabel, LV_ALIGN_TOP_LEFT, 0, y);

  /* Plant profile card (right) — slightly wider for stage/name strings */
  lv_obj_t *plantCard = gui_create_card(homeScreen, 152, 160);
  lv_obj_align(plantCard, LV_ALIGN_TOP_RIGHT, 0, 0);

  lv_obj_t *plantTitle = lv_label_create(plantCard);
  lv_label_set_text(plantTitle, "Plant");
  gui_style_section_title(plantTitle);
  lv_obj_align(plantTitle, LV_ALIGN_TOP_LEFT, 0, 0);

  y = 22;

  plantNameLabel = createReadingRow(plantCard, "Plant: --");
  lv_obj_align(plantNameLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  plantStageLabel = createReadingRow(plantCard, "Stage: --");
  lv_obj_align(plantStageLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  plantLightOnLabel = createReadingRow(plantCard, "Light: ---- min");
  lv_obj_align(plantLightOnLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  plantRGBLabel = createReadingRow(plantCard, "WRBN: --/--/--/--");
  lv_obj_align(plantRGBLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  plantDurationLabel = createReadingRow(plantCard, "Grow: --- days");
  lv_obj_align(plantDurationLabel, LV_ALIGN_TOP_LEFT, 0, y);
  y += rowGap;

  growingDaysLabel = createReadingRow(plantCard, "Day: ---");
  lv_obj_align(growingDaysLabel, LV_ALIGN_TOP_LEFT, 0, y);
  lv_obj_set_style_text_color(growingDaysLabel, gui_color(GUI_COLOR_ACCENT), 0);
}

void updatePlantProfileLabels(const struct plantProfile *p) {
  if (!p)
    return;

  growthDays = 1;
  enum growthStage stage = plant_getStage(p, growthDays);
  uint8_t blue = 0, red = 0, nir = 0;
  plant_getStageLights(p, stage, &blue, &red, &nir);

  lv_label_set_text_fmt(plantNameLabel, "%s", p->name);
  lv_label_set_text_fmt(plantStageLabel, "Stage: %s", getStageName(stage));

  lv_label_set_text_fmt(plantLightOnLabel, "Light: %u min", p->lightOnMinutes);
  lv_label_set_text_fmt(plantRGBLabel, "WRBN %u/%u/%u/%u",
                        p->whiteLightPercentage, red, blue, nir);

  lv_label_set_text_fmt(plantDurationLabel, "Grow: %lu d",
                        (unsigned long)p->growthDurationDays);
  lv_label_set_text_fmt(growingDaysLabel, "Day: %lu",
                        (unsigned long)growthDays);

  Lights_ApplyProfile(p);
}

void updateSensorLabels(float waterTemp, float enclosureTemp,
                        uint8_t waterLevelPct, float pH, float TDS) {
  if (!waterTempLabel || !enclosureTempLabel || !waterLevelLabel || !pHLabel ||
      !TDSLabel) {
    return;
  }

  lv_label_set_text_fmt(waterTempLabel, "Water: %.1f C", waterTemp);
  lv_label_set_text_fmt(enclosureTempLabel, "Encl: %.1f C", enclosureTemp);
  lv_label_set_text_fmt(waterLevelLabel, "Level: %u%%", waterLevelPct);
  lv_label_set_text_fmt(pHLabel, "pH: %.2f", pH);
  lv_label_set_text_fmt(TDSLabel, "TDS: %.0f ppm", TDS);
}
