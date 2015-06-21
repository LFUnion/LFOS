#include "stdint.h"
#include "idt.h"

#define NUM_OF_IDT_ENTRYS 1

uint64_t idt[NUM_OF_IDT_ENTRYS];

struct {
    uint16_t max_size;
    void* ptr;
} __attribute__((packed)) idt_ptr = {
    .max_size = NUM_OF_IDT_ENTRYS * 8 - 1,
    .ptr = idt,
};

void idt_add_entry ()