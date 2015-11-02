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

int strlen(char* string) {
    int len = 0;
    for (int i = 0; string[i] != '\0'; i++) {
	len++;
    }
    return len;
}
