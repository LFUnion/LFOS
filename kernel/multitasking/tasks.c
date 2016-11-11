#include "tasks.h"
#include "klib.h"
#include "kernel.h"

#define TASK_STACK_SIZE 4096

static uint32_t task_count = 0;
static uint32_t tasks_enabled = 0;
static uint32_t current_task = 0;
static task_t*  tasks[100];

static uint32_t request_count = 0;
static void*    first_request;

task_t* task_init(void* entry, char* name) {
    task_t* task = (task_t*)malloc(sizeof(task_t));
    uint8_t* stack = (uint8_t*)malloc(TASK_STACK_SIZE*sizeof(uint8_t));
    task->registers = (reg_state*)malloc(sizeof(reg_state));
    task->registers->eip = (uint32_t)task_crt0;
    task->registers->cs = 0x08;
    task->registers->ss = 0x10;
    task->registers->esp = (uint32_t)(stack+TASK_STACK_SIZE-1);
    task->registers->eflags = 0x202;
    task->stack = stack;
    task->task_id = task_count + 1;
    strcpy(task->task_name, name);
    task->entry = entry;
    task->enabled = 1;
    tasks_enabled++;
    task_count++;
    tasks[task_count] = task;
    return task;
}

void task_scheduler(reg_state* regs) {
    if (!task_count)
        return;

    if (current_task != 0)
        memcpy(regs, tasks[current_task]->registers, sizeof(reg_state));

    do {
        current_task++;

        if (current_task > task_count)
            current_task = 1;

        if (!tasks_enabled)
            abort("Scheduler: Deadlock detected! (No tasks are running)", 0);
    } while (tasks[current_task]->enabled == 0);

    memcpy(tasks[current_task]->registers, regs, sizeof(reg_state));
    return;
}

uint32_t task_get_id() {
    return current_task;
}

char* task_get_name(uint32_t id) {
    return tasks[id]->task_name;
}

void task_wait(int irq) {
    irq_request_t* request = (irq_request_t*)malloc(sizeof(irq_request_t));
    request->task_id = current_task;
    request->irq = irq;

    if (request_count == 0) {
        request->prev = request;
        first_request = request;
    } else {
        irq_request_t* prev = task_get_request(request_count-1);
        request->prev = prev;
        prev->next    = request;
    }

    request->next = request;
    request_count++;
    tasks[current_task]->enabled = 0;
    tasks_enabled--;
    asm volatile("int $0x20");
}

void task_stop(uint32_t id) {
    tasks[id]->enabled = 0;
    asm volatile("int $0x20");
}

void task_signal_irq(int irq) {
    if (request_count == 0)
        return;

    irq_request_t* request = 0x0;

    for (uint32_t i = 0; i < request_count; i++) {
        if (task_get_request(i)->irq == (uint32_t)irq) {
            request = task_get_request(i);
            break;
        }
    }

    if (request == 0x0)
        return;

    irq_request_t* prev = request->prev;
    irq_request_t* next = request->next;
    prev->next = next;
    next->prev = prev;
    tasks[request->task_id]->enabled = 1;
    tasks_enabled++;
    free(request);
    request_count--;
}

irq_request_t* task_get_request(uint32_t number) {
    if (request_count <= number)
        return 0x0;

    irq_request_t* current = first_request;

    for (uint32_t i = 0; i < number; i++)
        current = current->next;

    return current;
}

void task_crt0() {
    task_t* current_task = tasks[task_get_id()];

    void* mainfunc = current_task->entry;
    goto* mainfunc;

    task_stop(task_get_id());
}
