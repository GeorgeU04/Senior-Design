#include "touchscreen.h"
#include "main.h"
#include "stm32h7xx_hal_i2c.h"
#include <stdio.h>

HAL_StatusTypeDef initTouchScreen() {
  uint8_t gMode = 0;
  uint8_t threshold = 22;

  HAL_StatusTypeDef st;

  st = HAL_I2C_Mem_Write(&hi2c1, FT6206_ADR, G_MODE, I2C_MEMADD_SIZE_8BIT,
                         &gMode, 1, 20);
  if (st != HAL_OK)
    return st;

  st = HAL_I2C_Mem_Write(&hi2c1, FT6206_ADR, TH_GROUP, I2C_MEMADD_SIZE_8BIT,
                         &threshold, 1, 20);

  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchRead);
  return st;
}

void touchRead(lv_indev_t *indev, lv_indev_data_t *data) {
  (void)indev;
  static lv_point_t last = {0, 0};

  struct touchScreen t = {0};
  HAL_StatusTypeDef st = readTouchScreen(&t);

  if (st == HAL_OK && t.touched) {

    data->state = LV_INDEV_STATE_PRESSED;
    // i hate this stupid fucking touchscreen. It took so many attempts to
    // understand how the screen was rotating
    data->point.x = 239 - t.xPos;
    data->point.y = 319 - t.yPos;
    last = data->point;
  } else {
    data->state = LV_INDEV_STATE_RELEASED;
    data->point = last;
  }
}

HAL_StatusTypeDef readTouchScreen(struct touchScreen *touchData) {
  if (!touchData)
    return HAL_ERROR;

  touchData->touched = 0;

  uint8_t td = 0;
  HAL_StatusTypeDef st = HAL_I2C_Mem_Read(&hi2c1, FT6206_ADR, TD_STATUS,
                                          I2C_MEMADD_SIZE_8BIT, &td, 1, 20);
  if (st != HAL_OK)
    return st;

  if ((td & 0x0F) == 0)
    return HAL_OK;

  uint8_t data[4] = {0};
  st = HAL_I2C_Mem_Read(&hi2c1, FT6206_ADR, P1_XH, I2C_MEMADD_SIZE_8BIT, data,
                        sizeof(data), 20);
  if (st != HAL_OK)
    return st;

  touchData->xPos = (uint16_t)(((data[0] & 0x0F) << 8) | data[1]);
  touchData->yPos = (uint16_t)(((data[2] & 0x0F) << 8) | data[3]);
  touchData->touched = 1;
  return HAL_OK;
}
