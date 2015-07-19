#include "exceptionhandler.h"
#include "idt.h"
#include "cpu.h"

#include "klib.h"
#include "stdint.h"

extern void exc0();

void register_exception_handlers() {
    add_idt_gate(0, (uint32_t)exc0, 0x08, 0x8E);
}

void c_handler (struct registers *r) {
    printw("KERNEL PANIC");
    printw("Exception:");
    printd(r->int_no);
    printw("Halting");
    cpu_halt();
}