#include "climateControl.h"

void createCooler(struct cooler *cooler, GPIO_TypeDef *port, uint16_t pinMask) {
  cooler->port = port;
  cooler->pinMask = pinMask;
}

void turnOnCooler(struct cooler *cooler) {
  cooler->port->BSRR = (cooler->pinMask);
}

void turnOffCooler(struct cooler *cooler) {
  cooler->port->BSRR = (cooler->pinMask << 16);
}
