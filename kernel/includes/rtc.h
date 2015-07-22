#ifndef RTC_H
#define RTC_H

#include "stdint.h"

uint8_t rtc_second;
uint8_t rtc_minute;
uint8_t rtc_hour;

/* Refreshes the gloabl variables */
extern void rtc_refresh();

#endif /* RTC_H */