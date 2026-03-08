#include "DS18B20.h"
#include "main.h"
#include <stdint.h>

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

float readTemperature(struct DS18B20 sensor) {
  sendReset(sensor);
  writeByte(0xCC, sensor); // Skip ROM
  writeByte(0xBE, sensor); // Read scratchpad

  uint8_t lsb = readByte(sensor);
  uint8_t msb = readByte(sensor);

  int16_t raw_temp = (msb << 8) | lsb;

  return raw_temp / 16.0f;
}
