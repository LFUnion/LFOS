
/* 
 * This is an in-development feature.
 * In most cases, you are *NOT* able to compile this.
 */

#include "stdint.h"

#include "cpu.h"
#include "gdt.h"

#define NUM_OF_GDT_ENTRYS 256

extern void load_gdt_asm(void* desc)__attribute__((cdecl));

static uint64_t gdt[NUM_OF_GDT_ENTRYS];

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
    cpu_cli();
    
    struct {
        uint16_t size;
        uint32_t ptr;
    }__attribute__((packed)) gdt_ptr;
    
    gdt_ptr.size = NUM_OF_GDT_ENTRYS * 8 - 1;
    gdt_ptr.ptr = (uint32_t) gdt;
    
    load_gdt_asm(&gdt);
}
