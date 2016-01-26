#include "stdint.h"
#include "idt.h"
#include "klib.h"

#define NUM_OF_IDT_ENTRYS 256

idt_entry_t idt_entrys[NUM_OF_IDT_ENTRYS];
idt_ptr_t   idt_ptr2;

void add_idt_gate(int i, uint32_t base_addr, uint32_t selector, uint16_t flags)
{
    idt_entrys[i].base_low = base_addr & 0xFFFF;
    idt_entrys[i].base_low = (base_addr >> 16) & 0xFFFF;

    idt_entrys[i].selector = selector;
    idt_entrys[i].zero     = 0;

    idt_entrys[i].flags    = flags;
}

void init_idt() {

    idt_ptr2.limit = sizeof(idt_entry_t) * NUM_OF_IDT_ENTRYS -1;
    idt_ptr2.base  = (uint32_t)&idt_entrys;

    memset(&idt_entrys, 0, NUM_OF_IDT_ENTRYS * sizeof(uint64_t));

    add_idt_gate(0, (uint32_t)exc0, 0x08, 0x8E);
    add_idt_gate(1, (uint32_t)exc1, 0x08, 0x8E);
    add_idt_gate(2, (uint32_t)exc2, 0x08, 0x8E);
    add_idt_gate(3, (uint32_t)exc3, 0x08, 0x8E);
    add_idt_gate(4, (uint32_t)exc4, 0x08, 0x8E);
    add_idt_gate(5, (uint32_t)exc5, 0x08, 0x8E);
    add_idt_gate(6, (uint32_t)exc6, 0x08, 0x8E);
    add_idt_gate(7, (uint32_t)exc7, 0x08, 0x8E);
    add_idt_gate(8, (uint32_t)exc8, 0x08, 0x8E);
    add_idt_gate(9, (uint32_t)exc9, 0x08, 0x8E);
    add_idt_gate(10, (uint32_t)exc10, 0x08, 0x8E);
    add_idt_gate(11, (uint32_t)exc11, 0x08, 0x8E);
    add_idt_gate(12, (uint32_t)exc12, 0x08, 0x8E);
    add_idt_gate(13, (uint32_t)exc13, 0x08, 0x8E);
    add_idt_gate(14, (uint32_t)exc14, 0x08, 0x8E);
    add_idt_gate(15, (uint32_t)exc15, 0x08, 0x8E);
    add_idt_gate(16, (uint32_t)exc16, 0x08, 0x8E);
    add_idt_gate(17, (uint32_t)exc17, 0x08, 0x8E);
    add_idt_gate(18, (uint32_t)exc18, 0x08, 0x8E);
    add_idt_gate(19, (uint32_t)exc19, 0x08, 0x8E);
    add_idt_gate(20, (uint32_t)exc20, 0x08, 0x8E);
    add_idt_gate(21, (uint32_t)exc21, 0x08, 0x8E);
    add_idt_gate(22, (uint32_t)exc22, 0x08, 0x8E);
    add_idt_gate(23, (uint32_t)exc23, 0x08, 0x8E);
    add_idt_gate(24, (uint32_t)exc24, 0x08, 0x8E);
    add_idt_gate(25, (uint32_t)exc25, 0x08, 0x8E);
    add_idt_gate(26, (uint32_t)exc26, 0x08, 0x8E);
    add_idt_gate(27, (uint32_t)exc27, 0x08, 0x8E);
    add_idt_gate(28, (uint32_t)exc28, 0x08, 0x8E);
    add_idt_gate(29, (uint32_t)exc29, 0x08, 0x8E);
    add_idt_gate(30, (uint32_t)exc30, 0x08, 0x8E);
    add_idt_gate(31, (uint32_t)exc31, 0x08, 0x8E);

    flush_idt((uint32_t)&idt_ptr2);
}
