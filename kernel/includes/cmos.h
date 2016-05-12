#ifndef CMOS_H
#define CMOS_H

#include "stdint.h"

/* Address definitions */
#define COMMAND_ADDR 0x70
#define DATA_ADDR 0x71

uint8_t cmos_read_register(uint8_t reg);
void cmos_write_register(uint8_t reg, uint8_t data);

#endif /* CMOS_H */
