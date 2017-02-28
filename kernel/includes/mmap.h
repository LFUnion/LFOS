/*
 * mmap.h
 *
 *  Created on: Feb 28, 2017
 *      Author: fabian
 */

#ifndef KERNEL_INCLUDES_MMAP_H_
#define KERNEL_INCLUDES_MMAP_H_

#include <stdint.h>

#include "external/multiboot.h"
#include "klib.h"

multiboot_memory_map_t mmap[100];
uint32_t mmap_lenght;

void initialize_mmap(multiboot_info_t* mb_info);


#endif /* KERNEL_INCLUDES_MMAP_H_ */
