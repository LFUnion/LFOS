/*!
 * \file
 * \brief Dynamic memory management
 *
 * This file contains the dynamic memory management using the watermark method
 */

#include "mm_watermark.h"

/*!
 * \brief Adress pointer
 *
 * This is a pointer to the highest unused address
 */
void* first_addr = (void*)0x040000;
void* crnt_addr = (void*)0x040000; // 4MB
void* last_addr;

/*!
 * \brief Allocates memory
 *
 * This function allocates a block of memory of size n
 *
 * @param n Size of the memory to allocate
 * @return Pointer to the allocated block
 */

void  watermark_init() {
    uint32_t max_size = 0;
    uint32_t address;
    for (int i = 0; i < (int)mmap_lenght; ++i) {
        if (mmap[i].type == MULTIBOOT_MEMORY_AVAILABLE && mmap[i].len >= max_size) {
            max_size = mmap[i].len;
            address  = mmap[i].addr;
        }
    }

    first_addr = (void*)address;
    crnt_addr  = (void*)address;
    last_addr  = (void*)(address + max_size);
}

void* watermark_malloc (size_t n) {
    void* return_addr = crnt_addr;
    crnt_addr += n;

    if (crnt_addr >= last_addr)
        abort("Out of memory", NULL);

    return return_addr;
}

uint32_t watermark_available() {
    return (uint32_t)(last_addr - crnt_addr);
}

uint32_t watermark_used() {
    return (uint32_t)(crnt_addr - first_addr);
}
