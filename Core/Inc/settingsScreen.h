#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include "DS18B20.h"
#include "fans.h"
#include "src/core/lv_obj.h"
#include <stdint.h>

extern uint8_t useFahrenheit;

enum systemStatus {
  WATER_TEMP,
  ENCLOSURE_TEMP,
  PH_LEVEL,
  TDS_LEVEL,
  WATER_LEVEL,
  FAN_0,
  FAN_1,
  FAN_2,
  FAN_3
};

void drawSettingsScreen(lv_obj_t *settingsScreen);
void getSystemStatus();
#endif // !SETTINGSSCREEN_H
