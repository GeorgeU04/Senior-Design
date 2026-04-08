#ifndef WATERLEVELSENSOR_H
#define WATERLEVELSENSOR_H

#include "main.h"
#include <stdint.h>

struct waterLevelSensor {
  GPIO_TypeDef *onPort;
  uint16_t onPinMask;
  uint16_t onPin;
  ADC_HandleTypeDef *hadc;
};

uint32_t readWaterLevel(const struct waterLevelSensor *sensor);
void createWaterLevelSensor(struct waterLevelSensor *sensor,
                            GPIO_TypeDef *onPort, uint16_t onPinMask,
                            ADC_HandleTypeDef *hadc);

#endif // !WATERLEVELSENSOR_H
