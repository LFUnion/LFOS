#ifndef SERIAL_H
#define SERIAL_H

#include "stdint.h"

void serial_init();
void send(uint8_t chr);
uint8_t recv();

#endif /* SERIAL_H */