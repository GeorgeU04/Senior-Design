#include "DS3231s.h"
#include "main.h"
#include "stm32h7xx_hal_i2c.h"
#include <stdint.h>
#include <time.h>

void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
  uint8_t time[3];

  time[0] = ((seconds / 10) << 4) | (seconds % 10);
  time[1] = ((minutes / 10) << 4) | (minutes % 10);
  time[2] = ((hours / 10) << 4) | (hours % 10);

  HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, time, 3,
                    HAL_MAX_DELAY);
}

void setDate(uint8_t day) {
  day = ((day / 10) << 4) | (day % 10);
  HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, &day, 1,
                    HAL_MAX_DELAY);
}

void readDateData(uint8_t *date) {
  HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, date, 1,
                   HAL_MAX_DELAY);
}

void readTimeData(uint8_t *time) {
  HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, time, 4,
                   HAL_MAX_DELAY);
}

void parseTime(struct RTC_DS3231s *clock, uint8_t *time) {
  uint8_t seconds = 0;
  uint8_t minutes = 0;
  uint8_t hours = 0;
  // Seconds
  seconds = ((time[0] >> 4) * 10) + (time[0] & 0b1111);
  clock->seconds = seconds;
  // Minutes
  minutes = ((time[1] >> 4) * 10) + (time[1] & 0b1111);
  clock->minutes = minutes;
  // Hours
  if (time[2] & 0b01000000) { // 12 hour
    clock->is12Mode = 1;
    clock->isPM = time[2] & 0b00100000 ? 1 : 0;
    hours = (((time[2] & 0b11111) >> 4) * 10) + (time[2] & 0b1111);
    clock->hours = hours;
  } else { // 24 hour
    hours = ((time[2] >> 4) * 10) + (time[2] & 0b1111);
    clock->hours = hours;
    clock->isPM = 0;
    clock->is12Mode = 0;
  }
  // Day
  clock->day = time[3];
}
