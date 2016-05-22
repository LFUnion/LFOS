#ifndef CPU_H
#define CPU_H

void cpu_reset();
void cpu_halt();
void cpu_cli();
void cpu_sti();

char* cpu_getVendor();

#endif /* CPU_H */
