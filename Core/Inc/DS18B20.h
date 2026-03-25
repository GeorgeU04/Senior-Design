#ifndef DS18B20_H
#define DS18B20_H

#include "stm32h753xx.h"
#include <stdint.h>

enum DS18B20_State { DS18B20_IDLE, DS18B20_CONVERTING };

struct DS18B20 {
  GPIO_TypeDef *port;
  uint16_t pinMask;
  uint16_t pin;
};

struct DS18B20_Async {
  struct DS18B20 sensor;
  uint32_t startMS;
  uint32_t delayMS;
  enum DS18B20_State state;
  uint8_t validReading;
};

void createDS18B20Sensor(struct DS18B20 *sensor, GPIO_TypeDef *port,
                         uint16_t pinMask);
void createDS18B20Async(struct DS18B20_Async *async, struct DS18B20 sensor,
                        uint32_t delayMS);
void writeBit(uint8_t bit, struct DS18B20 sensor);
void writeByte(uint8_t byte, struct DS18B20 sensor);
uint8_t readBit(struct DS18B20 sensor);
uint8_t readByte(struct DS18B20 sensor);
uint8_t sendReset(struct DS18B20 sensor);
void startConversion(struct DS18B20 sensor);
uint8_t readTemperature(struct DS18B20 sensor, float *temp);
uint8_t asyncTemperatureReading(struct DS18B20_Async *asyncTemp, float *temp);

#endif // !DS18B20_H
