#include <stdint.h>
#include "indw.h"

uint32_t indw(uint16_t port)
{   
	
	// not insd
    uint32_t hex;
    asm volatile ("inl %1, %0\n" : "=a" (hex) : "d" (port));
    return hex;
}
