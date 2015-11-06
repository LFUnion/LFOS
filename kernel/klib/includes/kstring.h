#ifndef KSTRING_H
#define KSTRING_H

#include "stddef.h"

void* memcpy(void* str1_ptr, void* str2_ptr, size_t n);
void* memset(void* ptr, int value, size_t n);

int strlen(const char* string);
int strcmp (const char* s1, const char* s2);

#endif /* KSTRING_H */
