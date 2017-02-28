#ifndef KMEM_H
#define KMEM_H

#include "stdint.h"
#include "stddef.h"

#include "mm_watermark.h"
#include "mm_segmentation.h"

void  kmem_init();
uint32_t kmem_available();
uint32_t kmem_used();

void* malloc  (size_t n);
void* calloc  (size_t n);
void  free    (void* ptr);
void* realloc (void* ptr, size_t n);

#endif /* KMEM_H */
