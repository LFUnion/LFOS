#ifndef MM_SEGMENTATION_H
#define MM_SEGMENTATION_H

#include "stddef.h"
#include "stdint.h"

typedef struct {
    size_t lenght;  // Lenght of the memory segment
    int free : 1;   // Status of the segment (0=free, 1=used)
    uint16_t flags; // Flags (currently unused)
    void* prev;     // Previuos segment descriptor
    void* next;     // Next segment descriptor
} segment_descriptor;

void* segmentation_malloc(size_t n);
void  segmentation_free(void* ptr);
void* segmentation_new_descriptor(segment_descriptor* desc, segment_descriptor* prev, size_t lenght);
void* segmentation_use_descriptor(segment_descriptor* desc, segment_descriptor* prev, size_t lenght);

#endif /* MM_SEGMENTATION_H */
