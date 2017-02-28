#ifndef WATERMARK_H
#define WATERMARK_H

#include "mmap.h"
#include "kernel.h"

#include <stddef.h>
#include <stdint.h>

void  watermark_init();
void* watermark_malloc (size_t n);
void* watermark_calloc (const size_t n);

uint32_t watermark_available();
uint32_t watermark_used();

/*
// new code

void* ncalloc (size_t n, unsigned int size , double value);

void func_scalloc(short value, short* count_ptr, long max);
void func_icalloc(int value, int* count_ptr, long max);
void func_lcalloc(long value, long* count_ptr, long max);
void func_llcalloc(long long value, long long* count_ptr, long max);
void func_fcalloc(float value, float* count_ptr, long max);
void func_dcalloc(double value, double* count_ptr, long max);

void* calloc(size_t n, unsigned int size);
*/

#endif /* WATERMARK_H */
