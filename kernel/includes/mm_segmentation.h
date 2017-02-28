#ifndef MM_SEGMENTATION_H
#define MM_SEGMENTATION_H

#include "mmap.h"
#include "stddef.h"
#include <stdint.h>

// flag 0b 0000 0000 0000 0000

/* least significant bit
   Bit 0: if zero nothing else the segment is longer as the input size

   most significant bit
*/

typedef struct {
    size_t length;  // Length of the memory segment
    int free : 1;   // Status of the segment (0=free, 1=used)
    int last : 1;   // Is this the last descriptor? (0=no, 1=yes)
    uint16_t flags; // Flags
    void* prev;     // Previuos segment descriptor
    void* next;     // Next segment descriptor
} segment_descriptor;

void  segmentation_init();
void* segmentation_malloc(size_t n);
void  segmentation_free(void* ptr);
void* segmentation_new_descriptor(segment_descriptor* desc,
                                  segment_descriptor* prev, size_t length);
void* segmentation_use_descriptor(segment_descriptor* desc,
                                  segment_descriptor* prev, size_t length);

void* segmentation_calloc(size_t n);
void* free_segment_calloc (segment_descriptor* cur_desc,
                           segment_descriptor* prev_desc, size_t n);

uint32_t segmentation_available();
uint32_t segmentation_used();

#endif /* MM_SEGMENTATION_H */
