#include "pit.h"
#include "portio.h"
#include "stdint.h"

#define PIT_DATA 0x40
#define PIT_CMD  0x43

void pit_init(int frequency, int channel) {
    const uint16_t counter = 1193182 / frequency;
    const uint8_t  config  = 0b00110100;
    
    outb(PIT_CMD, config);
    outb(PIT_DATA+channel, counter);
    outb(PIT_DATA+channel, counter >> 8);
}
