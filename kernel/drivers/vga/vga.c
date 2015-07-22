#include <stdint.h>
#include "vga.h"
#include "portio.h"
#define TERM_ROWS 24

/*
LFOS, a simple operating system.
Copyright (C) 2015 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

int row = 0;
int column = 0;

// Prints a char (grey)
void kprintc(uint8_t chr, uint8_t clr, uint8_t x, uint8_t y) {
    uint16_t* offset = (uint16_t*)0xB8000;
    offset += y * 80 + x;
    *offset = ((uint16_t)clr) << 8 | chr;
}

// Prints a char (yellow)
void kprintci(uint8_t chr, uint8_t clr, uint8_t x, uint8_t y) {
    uint16_t* offset = (uint16_t*)0xB8000;
    offset += y * 80 + x;
    *offset = ((uint16_t)clr) << 9 | chr;
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

// Prints a highlighted message to the terminal
void klogi(const char text[]) {
    int i;
    
    for(i = 0; text[i] != '\0'; i++) {
        if(text[i] == '\n') {
            row++;
            column = 0;
            if(row > TERM_ROWS) {
                row = 0;
            }
        } else {
            kprintci(text[i], 0x07, column, row);
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
