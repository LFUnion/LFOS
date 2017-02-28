#ifndef KERNEL_H
#define KERNEL_H

#include "exceptionhandler.h"
#include "external/multiboot.h"

multiboot_info_t multiboot_info;

void kmain_task(void);
void abort(char* msg, registers_t* regs);
void idle();

#endif /* KERNEL_H */
