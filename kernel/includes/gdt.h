#ifndef GDT_H
#define GDT_H

#include "stdint.h"
#include "klib.h"

#include "cpu.h"

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
}
__attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
}
__attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

extern void flush_gdt(uint32_t pointer);

void add_gdt_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void load_gdt();

#endif /* GDT_H */
