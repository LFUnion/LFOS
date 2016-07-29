#include "mm_segmentation.h"

unsigned long descriptors_total = 0;
const segment_descriptor *first_desc = (segment_descriptor*)0x040000; // 4MB

void* segmentation_malloc(size_t n) {
    segment_descriptor *cur_desc = (segment_descriptor*)first_desc;
    segment_descriptor *prev_desc = (segment_descriptor*)40000;

    for (unsigned long i=0; i<descriptors_total; i++) {
        if (cur_desc->free == 0 && cur_desc->length >= n)
            return segmentation_use_descriptor(cur_desc, prev_desc, n);

        prev_desc = cur_desc;
        cur_desc = cur_desc->next;
    }

    return segmentation_new_descriptor(cur_desc, prev_desc, n);
}

void segmentation_free(void* ptr) {
    segment_descriptor *desc = (segment_descriptor*)(ptr - sizeof(
                                   segment_descriptor));
    segment_descriptor *next = (segment_descriptor*)desc->next;
    segment_descriptor *prev = (segment_descriptor*)desc->prev;
    desc->free = 0;

    if (prev->free == 0) {
        if (desc->last) {
            next = desc;
            prev->last = 1;
        }

        prev->next = next;
        next->prev = prev;
        prev->length += sizeof(segment_descriptor) + desc->length;
        next = prev->next;
        prev = prev->prev;
        desc = desc->prev;
        descriptors_total--;
    }

    if (desc->last == 0 && next->free == 0) {
        desc->length += sizeof(segment_descriptor) + next->length;
        next = next->next;
        ((segment_descriptor*)next->next)->prev = desc;
        descriptors_total--;
    }
}

void* segmentation_new_descriptor(segment_descriptor* desc,
                                  segment_descriptor* prev, size_t length) {
    desc->length = length;
    desc->free   = 1;
    desc->last   = 1;
    desc->flags  = 0;
    desc->prev   = prev;
    desc->next   = (void*)desc + sizeof(segment_descriptor) + length;
    descriptors_total++;
    prev->last   = 0;
    return (void*)desc + sizeof(segment_descriptor);
}

void* segmentation_use_descriptor(segment_descriptor* desc,
                                  segment_descriptor* prev, size_t length) {
    if ((void*)desc + length + 2*sizeof(segment_descriptor) + 1 <
            (void*)desc->next) {
        segment_descriptor* new_desc = (segment_descriptor*)((void*)desc + sizeof(
                                           segment_descriptor) + length);
        segmentation_new_descriptor(new_desc, desc,
                                    (void*)(desc->next)-((void*)new_desc+sizeof(segment_descriptor)));
        new_desc->next = desc->next;
        new_desc->last = 0;
        new_desc->free = 0;
        desc->next = new_desc;
    }

    desc->length = (size_t)((void*)(desc->next) - ((void*)desc + sizeof(
                                segment_descriptor)));
    desc->free   = 1;
    desc->flags  = 0;
    desc->prev   = prev;
    return (void*)desc + sizeof(segment_descriptor);
}
