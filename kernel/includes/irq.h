#ifndef IRQ_H
#define IRQ_H

#include "stdint.h"

typedef struct {
    uint32_t irq;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t eip, cs, eflags, useresp, ss;
} reg_state;

void irq_handler(reg_state regs);

#endif /* IRQ_H */
