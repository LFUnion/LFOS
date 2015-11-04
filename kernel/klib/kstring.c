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

int strlen(const char* string) {
    int len = 0;
    for (int i = 0; string[i] != '\0'; i++) {
	len++;
    }
    return len;
}

int strcmp (const char* s1, const char* s2) {
    if (strlen(s1) == strlen(s2)) {
	
	for (int i = 0; i < strlen(s1); i++) {
	    if (s1[i] == s2[i]) {
		continue;
	    } else {
		return 0;
	    }
	}

	return 1;

    } else {
	return 0;
    }
}
