#include "stdint.h"
#include "inb.h"

// Receives a value from a port
uint8_t inb(uint16_t port)
{
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}
