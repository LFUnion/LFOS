#include <stdint.h>
#include "outdw.h"


void outdw(uint16_t port, uint32_t hex) {
    // not outsd
    asm volatile ("outl %0, %1\n" : : "a"(hex), "d"(port));
}
