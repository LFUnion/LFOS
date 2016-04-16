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
int cursor_enabled = 1;

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

	if(column >= 80) {
	    row++;
        column = 0;
    if(row > TERM_ROWS) {
            scroll();
        }
	}

        if(text[i] == '\n') {
            row++;
            column = 0;
            if(row > TERM_ROWS) {
                scroll();


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

	if(column >= 80) {
	    row++;
            column = 0;
            if(row > TERM_ROWS) {
                row = 0;
            }
	}

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

    row++;
    column = 0;

    if(row > TERM_ROWS) {
        scroll();
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
        scroll();
    }
}

// Clears out the terminal
void kclear() {
    for(int i = 0; i < 25; i++) {
        klog("                                                                                ");
    }
    row = 0;
}

// Scrolls one line down
void scroll() {
    for (int i = 0; i < TERM_ROWS * 80; i++) {
            uint16_t* base = (uint16_t*)0xB8000;
            base += i;
            uint16_t* nchar = base + 80;
            *base = *nchar;
        }

        for (int i = 0
             ; i < 80; i++) {
            kprintc(' ', 0x07, i, 24);
        }

        row = 24;
}

// Returns the row
int vga_get_row() {
	return row;
}

// Returns the column
int vga_get_column() {
	return column;
}

// Sets a new position
void vga_set_position(int new_row, int new_column) {
	row = new_row;
	column = new_column;
}

// Updates the cursor
void vga_update_cursor() {
	vga_set_cursor(column, row);
}

// Sets the cursor position
void vga_set_cursor(int x, int y) {
	if (cursor_enabled) {
		int pos = y*80 + x;
		outb(0x3D4, 0x0F);
		outb(0x3D5, (unsigned char)(pos & 0xFF));
		outb(0x3D4, 0x0E);
		outb(0x3D5, (unsigned char)((pos >> 8)&0xFF));
	}
}

// Enables the cursor
void vga_enable_cursor() {
	if (!cursor_enabled) {
		cursor_enabled = 1;
		vga_set_cursor(255, 255);
	}
}

// Disables the cursor
void vga_disable_cursor() {
	if (cursor_enabled) {		
		vga_set_cursor(255, 255);
		cursor_enabled = 0;
	}
}
