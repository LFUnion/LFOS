#ifndef CPU_H
#define CPU_H

#include <stdint.h>

void cpu_reset();
void cpu_halt();
void cpu_cli();
void cpu_sti();

char* cpu_getVendor();
uint8_t get_number_of_cores();

#endif /* CPU_H */
