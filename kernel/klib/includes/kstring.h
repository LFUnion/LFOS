#ifndef KSTRING_H
#define KSTRING_H

#include "stddef.h"
#include "memmanager.h"

void* memcpy(void* str1_ptr, void* str2_ptr, size_t n);
void* memset(void* ptr, int value, size_t n);
//change old string
void strlowc (unsigned char* sl);
void strhighc (unsigned char* su);


int strlen(const char* string);
int strcmp (const char* s1, const char* s2);
unsigned char* strlow (const unsigned char* sl);
unsigned char* strhigh (const unsigned char* su);



#endif /* KSTRING_H */
