#ifndef KSTRING_H
#define KSTRING_H

#include "stddef.h"
#include "kmem.h"

void* memcpy(void* str1_ptr, void* str2_ptr, size_t n);
void* memset(void* ptr, int value, size_t n);
//change old string
void strlowc (char* sl);
void strhighc (char* su);


int strlen(const char* string);
int strcmp (const char* s1, const char* s2);
char* strlow (const char* sl);
char* strhigh (const char* su);



#endif /* KSTRING_H */
