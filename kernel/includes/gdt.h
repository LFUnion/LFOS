#ifndef GDT_H
#define GDT_H

void add_gdt_entry(int i, unsigned int base_addr, unsigned int size, int flags);
void load_gdt();

#endif /* GDT_H */