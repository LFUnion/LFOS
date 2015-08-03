#include "kstring.h"
#include "stddef.h"

void* memcpy(void* str1_ptr, void* str2_ptr, size_t n) {
    
    unsigned char* str1 = (unsigned char*) str1_ptr;
    unsigned char* str2 = (unsigned char*) str2_ptr;
    
    for(unsigned int i=0; i < n; i++) {
        str2[n] = str1[n];
    }
    
    return str2_ptr;
}