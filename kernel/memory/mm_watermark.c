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
void* crnt_addr = (void*)0x040000; // 4MB

/*!
 * \brief Allocates memory
 *
 * This function allocates a block of memory of size n
 *
 * @param n Size of the memory to allocate
 * @return Pointer to the allocated block
 */

void* watermark_malloc (size_t n) {
    void* return_addr = crnt_addr;
    crnt_addr += n;
    return return_addr;
}

