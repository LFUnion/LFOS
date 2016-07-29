#include "exceptionhandler.h"
#include "idt.h"
#include "cpu.h"

#include "klib.h"
#include "stdint.h"

void c_handler (registers_t r) {
    clear();
    char* msg = (char*)malloc(100*(sizeof(char*)));
    memset(msg, '\0', 100*(sizeof(char)));
    strcat(msg, "Unhandled exception. Error code: ");
    strcat(msg, (char*)itoa(r.int_no));
    abort(msg);
    return;
}
