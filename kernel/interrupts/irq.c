#include "stdint.h"
#include "klib.h"
#include "pic.h"

void irq_handler(uint32_t irq) {
    /*print_raw((char*)itoa(irq));
    print_raw(" ");*/
    pic_eoi((int)irq);
    return;
}
