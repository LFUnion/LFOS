#ifndef KMEM_H
#define KMEM_H

#include "stddef.h"

#include "watermark.h"
#include "mm_segmentation.h"

void* malloc (size_t n);
void  free   (void* ptr);

#endif /* KMEM_H */
