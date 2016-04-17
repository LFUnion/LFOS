#ifndef CPU_H
#define CPU_H

void cpu_reset();
void cpu_halt();
void cpu_cli();

char* cpu_getVendor();

#endif /* CPU_H */
