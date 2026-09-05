#ifndef CLIMATECONTROL_H
#define CLIMATECONTROL_H

#include "stm32h753xx.h"
#include <stdint.h>

struct cooler {
  GPIO_TypeDef *port;
  uint16_t pinMask;
};

void createCooler(struct cooler *cooler, GPIO_TypeDef *port, uint16_t pinMask);
void turnOnCooler(struct cooler *cooler);
void turnOffCooler(struct cooler *cooler);
#endif // !CLIMATE_CONTROL_H
