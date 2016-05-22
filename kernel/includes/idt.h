#ifndef IDT_H
#define IDT_H

#include "stdint.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  flags;
    uint16_t base_high;
}
__attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
}
__attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

void add_idt_gate(int i, uint32_t base_addr, uint32_t selector, uint16_t flags);
void init_idt();
extern void flush_idt(uint32_t);

// Exception handlers
extern void exc0  ();
extern void exc1  ();
extern void exc2  ();
extern void exc3  ();
extern void exc4  ();
extern void exc5  ();
extern void exc6  ();
extern void exc7  ();
extern void exc8  ();
extern void exc9  ();
extern void exc10 ();
extern void exc11 ();
extern void exc12 ();
extern void exc13 ();
extern void exc14 ();
extern void exc15 ();
extern void exc16 ();
extern void exc17 ();
extern void exc18 ();
extern void exc19 ();
extern void exc20 ();
extern void exc21 ();
extern void exc22 ();
extern void exc23 ();
extern void exc24 ();
extern void exc25 ();
extern void exc26 ();
extern void exc27 ();
extern void exc28 ();
extern void exc29 ();
extern void exc30 ();
extern void exc31 ();

extern void irq0  ();
extern void irq1  ();
extern void irq2  ();
extern void irq3  ();
extern void irq4  ();
extern void irq5  ();
extern void irq6  ();
extern void irq7  ();
extern void irq8  ();
extern void irq9  ();
extern void irq10 ();
extern void irq11 ();
extern void irq12 ();
extern void irq13 ();
extern void irq14 ();
extern void irq15 ();

#endif /* IDT_H */
