/*!
 * \file
 * \brief Process management
 *
 * This file contains functions which can get called by processes to manage their execution
 */

#include "process.h"
#include "rtc.h"

#include "stdint.h"

extern uint8_t rtc_second;

/*!
 * \brief Wait (time) seconds
 *
 * This function will halt the process until (time) seconds elapsed
 *
 * @param time The time (in seconds) to wait
 */
void wait(int time) 
{
    rtc_refresh(); // Refresh variables
    uint8_t start = rtc_second; // Set the startsecond to "now"
    uint8_t dest = start + time; // Calculate the dstinationsecond
    
    /* Only values < 60 are valid */
    if (dest >= 60)
    {
        dest -= 60;
    }
    
    /* Wait until the destiantion is reached */
    while (dest != rtc_second)
    {
        rtc_refresh();
    }
    
}
