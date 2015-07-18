#include "process.h"
#include "rtc.h"

#include "stdint.h"

extern uint8_t rtc_second;

void wait(int time) 
{
    rtc_refresh();
    uint8_t start = rtc_second;
    uint8_t dest = start + time;
    
    if (dest >= 60)
    {
        dest -= 60;
    }
    
    while (dest != rtc_second)
    {
        rtc_refresh();
    }
    
}
