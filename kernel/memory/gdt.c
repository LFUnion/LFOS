
/* 
 * This is an in-development feature.
 * In most cases, you are *NOT* able to compile this.
 */

#include "stdint.h"
#include "gdt.h"

#define NUM_OF_GDT_ENTRYS 256

void reload_segments()__attribute__((cdecl));

static uint64_t gdt[NUM_OF_GDT_ENTRYS];

struct {
    uint16_t size;
    void* ptr;
}__attribute__((packed)) gdt_ptr = {
    .size = NUM_OF_GDT_ENTRYS * 8 - 1,
    .ptr = gdt,
};

void add_gdt_entry(int i, unsigned int base_addr, unsigned int size, int flags)
{
    gdt[i] = size & 0xffffLL;
    gdt[i] |= (base_addr & 0xffffffLL) << 16;
    gdt[i] |= (flags & 0xffLL) << 40;
    gdt[i] |= ((size >> 16) & 0xfLL) << 48;
    gdt[i] |= ((flags >> 8 )& 0xffLL) << 52;
    gdt[i] |= ((base_addr >> 24) & 0xffLL) << 56;
}

void load_gdt()
{
    asm volatile("lgdt %0" : : "m" (gdt_ptr));
    reload_segments();
}
