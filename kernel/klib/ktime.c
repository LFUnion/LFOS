#include "ktime.h"
#include "rtc.h"

#include "stdint.h"

extern uint8_t rtc_second;
extern uint8_t rtc_minute;
extern uint8_t rtc_hour;

uint8_t get_second() {
    rtc_refresh();
    return rtc_second;
}

uint8_t get_minute() {
    rtc_refresh();
    return rtc_minute;
}

uint8_t get_hour() {
    rtc_refresh();
    return rtc_hour;
}