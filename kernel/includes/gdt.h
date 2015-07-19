#ifndef GDT_H
#define GDT_H

#include "stdint.h"

void add_gdt_entry(int i, uint32_t base_addr, uint32_t size, uint16_t flags);
void load_gdt();

#endif /* GDT_H */