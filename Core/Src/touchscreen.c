#include "touchscreen.h"
#include "main.h"
#include "stm32h753xx.h"
#include "stm32h7xx_hal_def.h"
#include "stm32h7xx_hal_i2c.h"
#include <stdint.h>

HAL_StatusTypeDef initTouchScreen(void) {
  uint8_t gMode = 0;
  uint8_t threshold = 22;

  HAL_StatusTypeDef st;

  st = HAL_I2C_IsDeviceReady(&hi2c1, FT6206_ADR, 3, 100);
  if (st != HAL_OK)
    return st;

  st = HAL_I2C_Mem_Write(&hi2c1, FT6206_ADR, G_MODE, I2C_MEMADD_SIZE_8BIT,
                         &gMode, 1, 100);
  if (st != HAL_OK)
    return st;

  st = HAL_I2C_Mem_Write(&hi2c1, FT6206_ADR, TH_GROUP, I2C_MEMADD_SIZE_8BIT,
                         &threshold, 1, 100);
  return st;
}

HAL_StatusTypeDef readTouchScreen(struct touchScreen *touchData) {
  if (!touchData)
    return HAL_ERROR;

  touchData->touched = 0;

  uint8_t td = 0;
  HAL_StatusTypeDef st = HAL_I2C_Mem_Read(&hi2c1, FT6206_ADR, TD_STATUS,
                                          I2C_MEMADD_SIZE_8BIT, &td, 1, 100);
  if (st != HAL_OK)
    return st;

  if ((td & 0x0F) == 0)
    return HAL_OK;

  uint8_t data[4] = {0};
  st = HAL_I2C_Mem_Read(&hi2c1, FT6206_ADR, P1_XH, I2C_MEMADD_SIZE_8BIT, data,
                        sizeof(data), 100);
  if (st != HAL_OK)
    return st;

  touchData->xPos = (uint16_t)(((data[0] & 0x0F) << 8) | data[1]);
  touchData->yPos = (uint16_t)(((data[2] & 0x0F) << 8) | data[3]);
  touchData->touched = 1;

  return HAL_OK;
}
