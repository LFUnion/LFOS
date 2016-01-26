
/*
 * This is an in-development feature.
 * In most cases, you are *NOT* able to run this.
 */

#include "gdt.h"

gdt_entry_t gdt_entrys[5];
gdt_ptr_t   gdt_ptr2;

void add_gdt_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entrys[i].base_low =    (base & 0xFFFF);
    gdt_entrys[i].base_middle = (base >> 16) & 0xFF;
    gdt_entrys[i].base_high =   (base >> 24) & 0xFF;

    gdt_entrys[i].limit_low =   (limit & 0xFFFF);
    gdt_entrys[i].granularity = (limit >> 16) & 0x0F;

    gdt_entrys[i].granularity |= gran & 0xF0;
    gdt_entrys[i].access =      access;
}

void load_gdt()
{
    cpu_cli();

    gdt_ptr2.limit  = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr2.base   = (uint32_t)&gdt_entrys;

    add_gdt_entry(0, 0, 0, 0, 0);
    add_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    add_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    add_gdt_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    add_gdt_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    flush_gdt((uint32_t)&gdt_ptr2);
}
