#include "stdint.h"
#include "klib.h"
#include "pic.h"

typedef struct {
    uint32_t irq;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t eip, cs, eflags, useresp, ss;
} reg_state;

void irq_handler(reg_state regs) {
    /*print_raw((char*)itoa(regs.irq));
    print_raw(" ");*/
    pic_eoi((int)regs.irq);
    return;
}
