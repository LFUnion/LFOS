#include "kio.h"

#include "vga.h"
#include "keyboard.h"

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

void printf(const char text[], ...) {
    klog(text);
}

char * scanf() {
    char* tmp = (char*)malloc(150 * sizeof(char));
    char inp = ' ';
    int i = 0;

    do {
	kbd_flush_buffer();
	inp = kbd_pull_char();
	
	if (inp != 0) {
	    char* str = (char*)malloc(sizeof(char));
            str[0] = inp;
            kprint_raw(str);
	    if (inp != '\n') {
	        tmp[i] = inp;
	    }

	    i++;
	}
    } while (inp != '\n');

    char* ret = (char*)malloc(strlen(tmp) * sizeof(char));
    
    for (int ii = 0; ii < strlen(tmp); ii++) {
	ret[ii] = tmp[ii];
    }

    return ret;
}

void printw(const char text[], ...) {
    klogi(text);
}

void print_raw(char text[]) {
    kprint_raw(text);
}

void __attribute__ ((deprecated)) printd(const int digit) {
    char string[1];
    string[0] = digit + '0';
    printf(string);
}

void clear() {
   kclear();
}
