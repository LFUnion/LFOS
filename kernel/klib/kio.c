/*!
 * \file
 * \brief Kernel Input/Output
 *
 * This file contains kernelspace IO functions
 */

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

/*!
 * \brief Print string
 *
 * This function prints the string to the console
 * @param text The string to print
 */
void printf(const char text[], ...) {
    klog(text);
}

/*!
 * \brief Read string from Keyboard
 *
 * This function pulls chars from the keyboard until enter is pressed
 * @return The pulled chars
 */
char * scanf() {
    char* tmp = (char*)malloc(150 * sizeof(char));
    char inp = ' ';
    int i = 0;

    vga_enable_cursor();

    do {
	vga_update_cursor();
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

    vga_disable_cursor();
    char* ret = (char*)malloc(strlen(tmp) * sizeof(char));
    
    for (int ii = 0; ii < strlen(tmp); ii++) {
	ret[ii] = tmp[ii];
    }

    return ret;
}

/*!
 * \brief Print warning
 *
 * This function also prints the string to the console, but the text will appear yellow
 * @param text The string to print
 */
void printw(const char text[], ...) {
    klogi(text);
}

void print_raw(char text[]) {
    kprint_raw(text);
}

/*!
 * \deprecated Use intToChar and printf instead
 * \brief Print digit
 *
 * This function prints a digit to the console
 * @param digit The digit to print
 */
void printd(const int digit) {
    char string[1];
    string[0] = digit + '0';
    printf(string);
}

/*!
 * \brief Clear screen
 *
 * This function clears the console
 */
void clear() {
   kclear();
}
