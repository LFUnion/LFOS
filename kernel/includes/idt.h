#ifndef IDT_H
#define IDT_H

#include "stdint.h"

void add_idt_gate(int i, uint32_t base_addr, uint32_t selector, uint16_t flags);
void init_idt();
void load_idt();

#endif /* IDT_H */
