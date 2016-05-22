#ifndef PIC_H
#define PIC_H

#include "stdint.h"

void pic_init();
void pic_mask(int pic, uint8_t mask);
void pic_eoi(int irq);

#endif /* PIC_H */
