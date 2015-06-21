#include <stdint.h>
#include "vga.h"

#define TERM_ROWS 24

int row = 0;
int column = 0;

// Prints a char
void kprintc(uint8_t chr, uint8_t clr, uint8_t x, uint8_t y) {
    uint16_t* offset = (uint16_t*)0xB8000;
    offset += y * 80 + x;
    *offset = ((uint16_t)clr) << 8 | chr;
}

// Prints raw text
void kprint_raw(const char text[]) {
    int i;
    
    for(i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n') {
            row++;
            column = 0;
            if(row > TERM_ROWS) {
                row = 0;
            }
        } else {
            kprintc(text[i], 0x07, column, row);
            column++;
        }
    }
}

// Prints a log message to the terminal
void klog(const char text[]) {
    int i;
    
    for(i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n') {
            row++;
            column = 0;
            if(row > TERM_ROWS) {
                row = 0;
            }
        } else {
            kprintc(text[i], 0x07, column, row);
            column++;
        }
    }
    column = 0;
    row++;
    if(row > TERM_ROWS) {
        row = 0;
    }
}

// Clears out the terminal
void kclear() {
    for(int i = 0; i < 25; i++) {
        klog("                                                                                ");
    }
}