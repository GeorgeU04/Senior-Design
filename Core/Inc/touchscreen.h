#ifndef TOUCHSCREEN_H
#define TOUCHSCREEN_H

#include "src/indev/lv_indev.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_def.h"
#include <stdint.h>

#define FT6206_ADR (0x38u << 1)
#define TD_STATUS 0x02
#define P1_XH 0x03
#define P1_XL 0x04
#define P1_YH 0x05
#define P1_YL 0x06
#define G_MODE 0xA4
#define TH_GROUP 0x80

struct touchScreen {
  uint16_t xPos;
  uint16_t yPos;
  uint8_t touched;
};

void touchRead(lv_indev_t *indev, lv_indev_data_t *data);
HAL_StatusTypeDef initTouchScreen();
HAL_StatusTypeDef readTouchScreen(struct touchScreen *touchData);
#endif // !TOUCHSCREEN_H
