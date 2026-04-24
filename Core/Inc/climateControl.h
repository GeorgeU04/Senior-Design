#ifndef CLIMATECONTROL_H
#define CLIMATECONTROL_H

#include "stm32h753xx.h"
#include <stdint.h>

struct heater {
  GPIO_TypeDef *port;
  uint16_t pinMask;
};

struct cooler {
  GPIO_TypeDef *port;
  uint16_t pinMask;
};

void createCooler(struct cooler *cooler, GPIO_TypeDef *port, uint16_t pinMask);
void createHeater(struct heater *heater, GPIO_TypeDef *port, uint16_t pinMask);
void turnOnCooler(struct cooler *cooler);
void turnOffCooler(struct cooler *cooler);
void turnOnHeater(struct heater *heater);
void turnOffHeater(struct heater *heater);
#endif // !CLIMATE_CONTROL_H
