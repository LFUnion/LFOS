#include "rtc.h"
#include "cmos.h"
#include "kio.h"

#include "stdint.h"

/*
 *  NOTE:
 *  This code is experimental.
 *  The functions are probably not stable
 *  on some machines.
 *
 */

/* Register definitions */
static uint8_t reg_sec = 0x00;
static uint8_t reg_min = 0x02;
static uint8_t reg_hor = 0x04;

/* Global variables */
extern uint8_t rtc_second;
extern uint8_t rtc_minute;
extern uint8_t rtc_hour;

/* Returns 0 if not currently updating */
static inline uint8_t read_update_flag() {
    return cmos_read_register(0x0A) & 0x80;
}

/* Refreshes the gloabl variables */
void rtc_refresh() {
    rtc_second = cmos_read_register(reg_sec);
    rtc_minute = cmos_read_register(reg_min);
    rtc_hour   = cmos_read_register(reg_hor);

    while(read_update_flag()) {
        rtc_second = cmos_read_register(reg_sec);
        rtc_minute = cmos_read_register(reg_min);
        rtc_hour   = cmos_read_register(reg_hor);
    }
}
