#include "kmem.h"
#include "kstring.h"

void* malloc (size_t n) {
#ifdef MM_WATERMARK
    return watermark_malloc(n);
#elif defined MM_SEGMENTATION
    return segmentation_malloc(n);
#else
#error "Configuration error: A memory manager MUST be used!"
#endif
}

void free (void* ptr) {
#ifdef MM_WATERMARK
#pragma message "The watermark memory manager does not support free()"
#elif defined MM_SEGMENTATION
    return segmentation_free(ptr);
#else
#error Configuration error: A memory manager MUST be used!
#endif
}

void* calloc (size_t n) {
    void* ptr = malloc(n);
    memset(ptr, 0, n);
    return ptr;
}

void* realloc (void* ptr, size_t n) {
    if (ptr == NULL)
        return malloc(n);

    void* newptr = malloc(n);
    memcpy(ptr, newptr, n);

    free(ptr);
    return newptr;
}
