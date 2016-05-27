#ifndef TASKS_H
#define TASKS_H

#include "irq.h"

typedef struct {
    uint32_t    task_id;
    reg_state*  registers;
    uint8_t*    stack;
} task_t;

task_t* task_init(void* entry);
void task_scheduler(reg_state* regs);

#endif /* TASKS_H */
