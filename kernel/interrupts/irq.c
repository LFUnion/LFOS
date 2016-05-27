#include "irq.h"
#include "klib.h"
#include "pic.h"
#include "tasks.h"

void irq_handler(reg_state regs) {
    /*print_raw((char*)itoa(regs.irq));
    print_raw(" ");*/
    
    if (regs.irq == 0) {
        task_scheduler(&regs);
    }
    
    pic_eoi((int)regs.irq);
    return;
}
