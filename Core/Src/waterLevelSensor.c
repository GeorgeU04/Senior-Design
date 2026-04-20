#include "waterLevelSensor.h"
#include "main.h"
#include "stm32h753xx.h"
#include "stm32h7xx_hal_adc.h"
#include <stdint.h>

static inline uint16_t pinIndexFromMask(uint16_t pinmask) {
  return (uint16_t)__builtin_ctz((uint32_t)pinmask); // count trailing zeros
}

static inline uint32_t map(uint32_t x, uint32_t inMin, uint32_t inMax,
                           uint32_t outMin, uint32_t outMax) {
  if (x < inMin)
    x = inMin;
  else if (x > inMax)
    x = inMax;
  return (x - inMin) * (outMax - outMin + 1) / (inMax - inMin + 1) + outMin;
}

void createWaterLevelSensor(struct waterLevelSensor *sensor,
                            GPIO_TypeDef *onPort, uint16_t onPinMask,
                            ADC_HandleTypeDef *hadc) {
  sensor->onPort = onPort;
  sensor->onPinMask = onPinMask;
  sensor->onPin = pinIndexFromMask(onPinMask);
  sensor->hadc = hadc;
}

uint32_t readWaterLevel(const struct waterLevelSensor *sensor) {
  sensor->onPort->BSRR = (sensor->onPinMask);
  HAL_Delay(20);
  HAL_ADC_Start(sensor->hadc);
  HAL_ADC_PollForConversion(sensor->hadc, 100);
  uint32_t raw = HAL_ADC_GetValue(sensor->hadc);
  HAL_ADC_Stop(sensor->hadc);
  sensor->onPort->BSRR = (sensor->onPinMask << 16);
  return raw;
}
