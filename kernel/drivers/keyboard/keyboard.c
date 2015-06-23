#include "stdint.h"
#include "portio.h"

// Keyboard controller port: 0x60

int kbd_detect()
{
    outb(0x60, 0xEE); // Sending echo command
    uint8_t response = inb(0x60); // Waiting for response
    if(response == 0xEE || response == 0xFE) {
        return 1;
    } else {
        return 0;
    }
}