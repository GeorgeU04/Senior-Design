#ifndef DS3231S_H
#define DS3231S_H

#include <stdint.h>

#define DS3231_ADDRESS (0x68 << 1)

struct RTC_DS3231s {
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t isPM;
  uint8_t is12Mode;
  uint8_t day;
};

void setDay(uint8_t day);
void readDateData(uint8_t *date);
void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds);
void readTimeData(uint8_t *time);
void parseTime(struct RTC_DS3231s *clock, uint8_t *time);
void parseDate(struct RTC_DS3231s *clock, uint8_t *time);

#endif // !DS3231S_H
