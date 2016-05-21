#include "exceptionhandler.h"
#include "idt.h"
#include "cpu.h"

#include "klib.h"
#include "stdint.h"

void c_handler (registers_t r) {
    clear();
    abort("Unhandled exception");
    return;
}
