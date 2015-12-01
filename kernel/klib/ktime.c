/*!
 * \file
 * \brief Time and date functions
 *
 * This file contains functions which access varios clock drivers to provide date and time information
 */

#include "ktime.h"
#include "rtc.h"

#include "stdint.h"

/*!
 * Current second
 */
extern uint8_t rtc_second;

/*!
 * Current minute
 */
extern uint8_t rtc_minute;

/*!
 * Current hour
 */
extern uint8_t rtc_hour;

/*!
 * \brief Get current second
 *
 * This function refreshes the system time and returns the current second
 * @return Current second
 */
uint8_t get_second() {
    rtc_refresh();
    return rtc_second;
}

/*!
 * \brief Get current minute
 *
 * This function refreshes the system time and returns the current minute
 * @return Current minute
 */
uint8_t get_minute() {
    rtc_refresh();
    return rtc_minute;
}

/*!
 * \brief Get current hour
 *
 * This function refreshes the system time and returns the current hour
 * @return Current hour
 */
uint8_t get_hour() {
    rtc_refresh();
    return rtc_hour;
}