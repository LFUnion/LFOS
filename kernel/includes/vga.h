#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void kprintc(uint8_t chr, uint8_t clr, uint8_t x, uint8_t y);
void kprint_raw(const char text[]);
void klog(const char text[]);
void kclear();

#endif