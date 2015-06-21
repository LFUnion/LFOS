#ifndef IDT_H
#define IDT_H

void add_idc_gate(int i, unsigned int base_addr, unsigned int selector, int flags);
void load_idt();

#endif /* IDT_H */