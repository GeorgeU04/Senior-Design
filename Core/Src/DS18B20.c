#include "DS18B20.h"
#include "main.h"
#include <stdint.h>

void DS18B20_Delay_us(uint16_t us) {
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  HAL_TIM_Base_Start(&htim2);

  while (__HAL_TIM_GET_COUNTER(&htim2) < us)
    ;
}

void writeBit(uint8_t bit) {
  GPIOB->MODER &= ~(0b11 << (2 * DS18B20_PIN));
  GPIOB->MODER |= (0b01 << (2 * DS18B20_PIN)); // set as output
  GPIOB->BSRR = (1 << (DS18B20_PIN + 16));     // pull low

  if (bit == 0) {
    DS18B20_Delay_us(60);
    GPIOB->BSRR = (1 << (DS18B20_PIN)); // pull high
  } else {
    DS18B20_Delay_us(10);
    GPIOB->BSRR = (1 << (DS18B20_PIN)); // pull high
    DS18B20_Delay_us(50);
  }
}

void writeByte(uint8_t byte) {
  for (uint8_t i = 0; i < 8; ++i) {
    writeBit(byte & 0x01);
    byte >>= 1;
  }
}

uint8_t readBit(void) {
  uint8_t bit = 0;

  GPIOB->MODER &= ~(0b11 << (2 * DS18B20_PIN));
  GPIOB->MODER |= (0b01 << (2 * DS18B20_PIN)); // set as output
  GPIOB->BSRR = (1 << (DS18B20_PIN + 16));     // pull low
  DS18B20_Delay_us(5);

  GPIOB->MODER &= ~(0b11 << (2 * DS18B20_PIN)); // set as input
  DS18B20_Delay_us(15);

  if (GPIOB->IDR & (1 << DS18B20_PIN)) {
    bit = 1;
  }
  DS18B20_Delay_us(45);

  return bit;
}

uint8_t readByte(void) {
  uint8_t byte = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    byte |= (readBit() << i);
  }
  return byte;
}

uint8_t sendReset(void) {
  uint8_t response = 0;

  GPIOB->MODER &= ~(0b11 << (2 * DS18B20_PIN));
  GPIOB->MODER |= (0b01 << (2 * DS18B20_PIN)); // set as output

  GPIOB->BSRR = (1 << (DS18B20_PIN + 16)); // pull low
  DS18B20_Delay_us(480);

  GPIOB->MODER &= ~(0b11 << (2 * DS18B20_PIN)); // set as input
  DS18B20_Delay_us(60);

  if (!(GPIOB->IDR & (1 << DS18B20_PIN))) {
    response = 1;
  }
  DS18B20_Delay_us(420);

  return response;
}

void startConversion(void) {
  sendReset();
  writeByte(0xCC); // Skip ROM
  writeByte(0x44); // Start conversion
}

float readTemperature(void) {
  sendReset();
  writeByte(0xCC); // Skip ROM
  writeByte(0xBE); // Read scratchpad

  uint8_t lsb = readByte();
  uint8_t msb = readByte();

  int16_t raw_temp = (msb << 8) | lsb;

  return raw_temp / 16.0;
}
