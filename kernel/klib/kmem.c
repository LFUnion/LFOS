#include "kmem.h"

void* malloc (size_t n) {
    #ifdef MM_WATERMARK
    return watermark_malloc(n);
    #else
    #error "Configuration error: A memory manager MUST be used!"
    #endif
}

void free (void* ptr) {
    #ifdef MM_WATERMARK
    #pragma message "The watermark memory manager does not support free()"
    #else
    #error Configuration error: A memory manager MUST be used!
    #endif
}
