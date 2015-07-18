#include "rtc.h"
#include "portio.h"
#include "kio.h"

#include "stdint.h"

/*
 *  NOTE: 
 *  This code is experimental.
 *  The functions are probably not stable
 *  on some machines.
 * 
 */

/* Address definitions */
static uint16_t command_addr = 0x70;
static uint16_t data_addr = 0x71;

/* Register definitions */
static uint8_t reg_sec = 0x00;
static uint8_t reg_min = 0x02;
static uint8_t reg_hor = 0x04;

/* Global variables */
extern uint8_t rtc_second;
extern uint8_t rtc_minute;
extern uint8_t rtc_hour;

static inline uint8_t read_register(uint8_t reg)
{
    outb(command_addr, reg);
    return inb(data_addr);
}

void rtc_refresh()
{
    rtc_second = read_register(reg_sec);
    rtc_minute = read_register(reg_min);
    rtc_hour   = read_register(reg_hor);
}