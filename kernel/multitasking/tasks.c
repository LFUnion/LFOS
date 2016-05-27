#include "tasks.h"
#include "klib.h"

static uint32_t task_count = 0;
static uint32_t current_task = 0;
static task_t*  tasks[100];

task_t* task_init(void* entry) {
    task_t* task = (task_t*)malloc(sizeof(task_t));
    uint8_t* stack = (uint8_t*)malloc(4096*sizeof(uint8_t));
    
    task->registers = (reg_state*)malloc(sizeof(reg_state));
    task->registers->eip = (uint32_t)entry;
    task->registers->cs = 0x08;
    task->registers->ss = 0x10;
    task->registers->esp = (uint32_t)stack;
    task->registers->eflags = 0x202;
    
    task->stack = stack;
    task->task_id = task_count + 1;

    task_count++;
    tasks[task_count] = task;
    
    return task;
}

void task_scheduler(reg_state* regs) {
    if (!task_count)
        return;
    
    if (current_task != 0) {
        memcpy(regs, tasks[current_task]->registers, sizeof(reg_state));
    }
    
    current_task++;
    if (current_task > task_count)
        current_task = 1;
    
    memcpy(tasks[current_task]->registers, regs, sizeof(reg_state));
    
    return;
}
