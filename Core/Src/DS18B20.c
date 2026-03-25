#include "DS18B20.h"
#include "main.h"
#include <stddef.h>
#include <stdint.h>

static inline uint16_t pinIndexFromMask(uint16_t pinmask) {
  return (uint16_t)__builtin_ctz((uint32_t)pinmask); // count trailing zeros
}
void createDS18B20Sensor(struct DS18B20 *sensor, GPIO_TypeDef *port,
                         uint16_t pinMask) {
  sensor->pin = pinIndexFromMask(pinMask);
  sensor->pinMask = pinMask;
  sensor->port = port;
}

void createDS18B20Async(struct DS18B20_Async *async, struct DS18B20 sensor,
                        uint32_t delayMS) {
  async->state = DS18B20_IDLE;
  async->sensor = sensor;
  async->delayMS = delayMS;
  async->state = 0;
}

void DS18B20_Delay_us(uint16_t us) {
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  HAL_TIM_Base_Start(&htim2);

  while (__HAL_TIM_GET_COUNTER(&htim2) < us)
    ;
  HAL_TIM_Base_Stop(&htim2);
}

void writeBit(uint8_t bit, struct DS18B20 sensor) {
  sensor.port->MODER &= ~(0b11 << (sensor.pin * 2));
  sensor.port->MODER |= (0b01 << (sensor.pin * 2)); // set as output
  sensor.port->BSRR = (sensor.pinMask << 16);       // pull low

  if (bit == 0) {
    DS18B20_Delay_us(60);
    sensor.port->BSRR = (sensor.pinMask); // pull high
  } else {
    DS18B20_Delay_us(10);
    sensor.port->BSRR = (sensor.pinMask); // pull high
    DS18B20_Delay_us(50);
  }
}

void writeByte(uint8_t byte, struct DS18B20 sensor) {
  for (uint8_t i = 0; i < 8; ++i) {
    writeBit(byte & 0x01, sensor);
    byte >>= 1;
  }
}

uint8_t readBit(struct DS18B20 sensor) {
  uint8_t bit = 0;

  sensor.port->MODER &= ~(0b11 << (2 * sensor.pin));
  sensor.port->MODER |= (0b01 << (2 * sensor.pin)); // set as output
  sensor.port->BSRR = (sensor.pinMask << 16);       // pull low
  DS18B20_Delay_us(5);

  sensor.port->MODER &= ~(0b11 << (2 * sensor.pin)); // set as input
  DS18B20_Delay_us(15);

  if (sensor.port->IDR & (sensor.pinMask)) {
    bit = 1;
  }
  DS18B20_Delay_us(45);

  return bit;
}

uint8_t readByte(struct DS18B20 sensor) {
  uint8_t byte = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    byte |= (readBit(sensor) << i);
  }
  return byte;
}

uint8_t sendReset(struct DS18B20 sensor) {
  uint8_t response = 0;

  sensor.port->MODER &= ~(0b11 << (2 * sensor.pin));
  sensor.port->MODER |= (0b01 << (2 * sensor.pin)); // set as output

  sensor.port->BSRR = (sensor.pinMask << 16); // pull low
  DS18B20_Delay_us(480);

  sensor.port->MODER &= ~(0b11 << (2 * sensor.pin)); // set as input
  DS18B20_Delay_us(60);

  if (!(sensor.port->IDR & (sensor.pinMask))) {
    response = 1;
  }
  DS18B20_Delay_us(420);

  return response;
}

void startConversion(struct DS18B20 sensor) {
  sendReset(sensor);
  writeByte(0xCC, sensor); // Skip ROM
  writeByte(0x44, sensor); // Start conversion
}

uint8_t readTemperature(struct DS18B20 sensor, float *temp) {
  uint8_t scratchPad[9];
  if (!sendReset(sensor))
    return 0;
  writeByte(0xCC, sensor); // Skip ROM
  writeByte(0xBE, sensor); // Read scratchpad

  uint8_t calculatedCrc = 0;
  for (uint8_t i = 0; i < 9; ++i)
    scratchPad[i] = readByte(sensor);

  // x^8 + x^5 + x^4 + x^0 = 0b00110001 = 0x31
  // ignore the x^8 as CRC 8 always has that anyways
  // 0x31 must be flipped as we are shifting right (LSB first) which gives 0x8C
  for (uint8_t i = 0; i < 8; ++i) {
    uint8_t input = scratchPad[i];
    for (uint8_t j = 0; j < 8; ++j) {
      uint8_t mix = (calculatedCrc ^ input) & 0x01;
      calculatedCrc >>= 1;
      if (mix)
        calculatedCrc ^= 0x8C;
      input >>= 1;
    }
  }

  if (calculatedCrc != scratchPad[8])
    return 0;

  int16_t rawTemp = (int16_t)(((uint16_t)(scratchPad[1] << 8)) | scratchPad[0]);
  *temp = rawTemp / 16.0f;
  return 1;
}

uint8_t asyncTemperatureReading(struct DS18B20_Async *asyncDS18B20,
                                float *temp) {
  uint32_t now = HAL_GetTick();
  switch (asyncDS18B20->state) {
  case DS18B20_IDLE:
    startConversion(asyncDS18B20->sensor);
    asyncDS18B20->startMS = now;
    asyncDS18B20->state = DS18B20_CONVERTING;
    return 0;
  case DS18B20_CONVERTING:
    if ((now - asyncDS18B20->startMS) >= asyncDS18B20->delayMS) {
      asyncDS18B20->validReading = readTemperature(asyncDS18B20->sensor, temp);
      asyncDS18B20->state = DS18B20_IDLE;
      return 1;
    }
    return 0;
  }
  return 0;
}
