
/* 
 * This is an in-development feature.
 * In most cases, you are *NOT* able to compile this.
 */


#include "stdint.h"
#include "idt.h"

#define NUM_OF_IDT_ENTRYS 256

static uint64_t idt[NUM_OF_IDT_ENTRYS];

struct {
    uint16_t limit;
    void* ptr;
}__attribute__((packed)) idt_ptr = {
    .limit = NUM_OF_IDT_ENTRYS * 8 - 1,
    .ptr = idt,
};

void add_idc_gate(int i, unsigned int base_addr, unsigned int selector, int flags)
{
    idt[i] = size & 0xffffLL;
    idt[i] |= (base_addr & 0xffffffLL) << 16; // base_addr low
    idt[i] |= (selector & 0xffLL) << 32;
    idt[i] |= ((0 >> 16) & 0xfLL) << 40;
    idt[i] |= ((flags >> 8 )& 0xffLL) << 48;
    idt[i] |= ((base_addr >> 24) & 0xffLL) << 64; // base_addr high
}

void load_idc()
{
    asm volatile("lidt %0" : : "m" (idt_ptr));
}