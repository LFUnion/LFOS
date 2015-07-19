#include "stdint.h"
#include "idt.h"

#define NUM_OF_IDT_ENTRYS 256


static uint64_t idt[NUM_OF_IDT_ENTRYS];

void add_idt_gate(int i, uint32_t base_addr, uint32_t selector, uint16_t flags)
{
    // idt[i] = 64 & 0xffffLL; // Only uncomment if *REALLY* needed
    
    idt[i] |= (base_addr & 0xffffffLL) << 16; // base_addr low
    idt[i] |= (selector & 0xffLL) << 32;
    idt[i] |= ((0 >> 16) & 0xfLL) << 40;
    idt[i] |= ((flags >> 8 )& 0xffLL) << 48;
    idt[i] |= ((base_addr >> 24) & 0xffLL) << 64; // base_addr high
}

void load_idt()
{
    struct {
        uint16_t limit;
        uint32_t ptr;
    }__attribute__((packed)) idt_ptr;
    
    idt_ptr.limit = NUM_OF_IDT_ENTRYS * 8 - 1;
    idt_ptr.ptr = (uint32_t) idt;
    
    asm("lidt %0" : : "m"(idt_ptr));
}