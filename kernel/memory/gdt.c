
/* 
 * This is an in-development feature.
 * In most cases, you are *NOT* able to run this.
 */

#include "stdint.h"
#include "klib.h"

#include "cpu.h"
#include "gdt.h"

#define NUM_OF_GDT_ENTRYS 256

extern void load_gdt_asm(void* desc)__attribute__((cdecl));
static uint64_t gdt[NUM_OF_GDT_ENTRYS];

inline void add_gdt_entry(int i, uint32_t base_addr, uint32_t size, uint16_t flags)
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
    
    add_gdt_entry(0, 0, 0, 0);
    add_gdt_entry(1, 0, 0x000FFFFF, (((1) << 0x04) | ((1) << 0x07) | ((0) << 0x0C) | ((0) << 0x0D) | ((1) << 0x0E) | ((1) << 0x0F) | (((0) & 0x03) << 0x05) | 0x0A));
    add_gdt_entry(2, 0, 0x000FFFFF, (((1) << 0x04) | ((1) << 0x07) | ((0) << 0x0C) | ((0) << 0x0D) | ((1) << 0x0E) | ((1) << 0x0F) | (((0) & 0x03) << 0x05) | 0x02));
    add_gdt_entry(3, 0, 0x000FFFFF, (((1) << 0x04) | ((1) << 0x07) | ((0) << 0x0C) | ((0) << 0x0D) | ((1) << 0x0E) | ((1) << 0x0F) | (((3) & 0x03) << 0x05) | 0x0A));
    add_gdt_entry(4, 0, 0x000FFFFF, (((1) << 0x04) | ((1) << 0x07) | ((0) << 0x0C) | ((0) << 0x0D) | ((1) << 0x0E) | ((1) << 0x0F) | (((3) & 0x03) << 0x05) | 0x02));

    
    struct {
        uint16_t size;
        void* ptr;
    }__attribute__((packed)) gdt_ptr = {
        .size = NUM_OF_GDT_ENTRYS * 8 - 1,
        .ptr = &gdt,
    };
    
    //load_gdt_asm(&gdt_ptr);
}
