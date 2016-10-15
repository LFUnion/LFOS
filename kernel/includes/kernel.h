#ifndef KERNEL_H
#define KERNEL_H

#include "exceptionhandler.h"

void kmain_task(void);
void abort(char* msg, registers_t* regs);
void idle();

#endif /* KERNEL_H */
