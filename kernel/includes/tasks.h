#ifndef TASKS_H
#define TASKS_H

#include "irq.h"

typedef struct {
    uint32_t    task_id;
    char        task_name[30];
    reg_state*  registers;
    uint8_t*    stack;
    uint8_t     enabled : 1;
} task_t;

typedef struct {
    uint32_t task_id;
    uint32_t irq;
    void*    next;
    void*    prev;
} irq_request_t;


task_t*         task_init(void* entry, char* name);
void            task_scheduler(reg_state* regs);
uint32_t        task_get_id();
char*           task_get_name(uint32_t id);
void            task_wait(int irq);
void            task_stop(uint32_t id);
void            task_signal_irq(int irq);
irq_request_t*  task_get_request(uint32_t number);

#endif /* TASKS_H */
