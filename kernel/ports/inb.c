#include "stdint.h"
#include "inb.h"

uint8_t inb(uint16_t port)
{
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}
