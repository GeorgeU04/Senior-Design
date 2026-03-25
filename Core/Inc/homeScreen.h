#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include "plantProfiles.h"
#include "src/core/lv_obj.h"
#include <stdint.h>

/* Sensor labels */
extern lv_obj_t *waterTempLabel;
extern lv_obj_t *enclosureTempLabel;
extern lv_obj_t *waterLevelLabel;
extern lv_obj_t *pHLabel;
extern lv_obj_t *TDSLabel;

/* Plant profile labels */
extern lv_obj_t *plantNameLabel;
extern lv_obj_t *plantStageLabel;
extern lv_obj_t *plantLightOnLabel;
extern lv_obj_t *plantRGBLabel;
extern lv_obj_t *plantDurationLabel;
extern lv_obj_t *growingDaysLabel;

extern uint32_t growthDays;

void drawHomeScreen(lv_obj_t *homeScreen);
void updatePlantProfileLabels(const struct plantProfile *profile);

void updateSensorLabels(float waterTempC, float enclosureTempC,
                        uint8_t waterLevelPct, float pH, float tds_ppm);
#endif // !HOMESCREEN_H
