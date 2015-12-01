/*!
 * \file
 * \brief Dynamic memory management
 *
 * This file contains the dynamic memory management
 */

#include "memmanager.h"

// This is just a very simple MM to start with

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

void* malloc (size_t n) {
    void* return_addr = crnt_addr;
    crnt_addr += n;
    return return_addr;
}
