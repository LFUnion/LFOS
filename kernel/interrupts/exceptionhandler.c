#include "exceptionhandler.h"
#include "idt.h"
#include "cpu.h"

#include "klib.h"
#include "stdint.h"

void c_handler (registers_t r) {
    clear();
    printw("KERNEL PANIC");
    printw("Exception:");
    print_raw((char*)stringFromInt((int)r.int_no));
    printw("Halting");
    cpu_halt();
    return;
}
