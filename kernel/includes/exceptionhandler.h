#ifndef EXCEPTIONHANDLER_H
#define EXCEPTIONHANDLER_H

#include <stdint.h>

void register_exception_handlers();

typedef struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;

#endif /* EXCEPTIONHANDLER_H */
