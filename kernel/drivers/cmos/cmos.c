#include "cmos.h"
#include "portio.h"

/* Reads a register of the CMOS memory */
uint8_t cmos_read_register(uint8_t reg) {
    outb(COMMAND_ADDR, reg);
    return inb(DATA_ADDR);
}

/* Writes to a CMOS register */
void cmos_write_register(uint8_t reg, uint8_t data) {
    outb(COMMAND_ADDR, reg);
    outb(DATA_ADDR, data);
}
