#include "climateControl.h"

void createCooler(struct cooler *cooler, GPIO_TypeDef *port, uint16_t pinMask) {
  cooler->port = port;
  cooler->pinMask = pinMask;
}

void createHeater(struct heater *heater, GPIO_TypeDef *port, uint16_t pinMask) {
  heater->port = port;
  heater->pinMask = pinMask;
}

void turnOnCooler(struct cooler *cooler) {
  cooler->port->BSRR = (cooler->pinMask);
}

void turnOffCooler(struct cooler *cooler) {
  cooler->port->BSRR = (cooler->pinMask << 16);
}

void turnOnHeater(struct heater *heater) {
  heater->port->BSRR = (heater->pinMask);
}

void turnOffHeater(struct heater *heater) {
  heater->port->BSRR = (heater->pinMask << 16);
}
