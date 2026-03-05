#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>

void writeBit(uint8_t bit);
void writeByte(uint8_t byte);
uint8_t readBit(void);
uint8_t readByte(void);
uint8_t sendReset(void);
void startConversion(void);
float readTemperature(void);

#endif // !DS18B20_H
