#ifndef DS18B20_H
#define DS18B20_H

#include "stm32h753xx.h"
#include <stdint.h>

struct DS18B20 {
  GPIO_TypeDef *port;
  uint16_t pinMask;
  uint16_t pin;
};

void writeBit(uint8_t bit, struct DS18B20 sensor);
void writeByte(uint8_t byte, struct DS18B20 sensor);
uint8_t readBit(struct DS18B20 sensor);
uint8_t readByte(struct DS18B20 sensor);
uint8_t sendReset(struct DS18B20 sensor);
void startConversion(struct DS18B20 sensor);
float readTemperature(struct DS18B20 sensor);

#endif // !DS18B20_H
