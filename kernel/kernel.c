// Include the IO library, alternatively you can import the VGA driver (includes/vga.h)
#include "../clib/includes/stdio.h"

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

// Display head
void kmain(void) {
    clear();
    printf("Welcome to LFOS!");
    printf("(C) 2015 by LFUnion");
    printf("");
    printf("Compiled");
    printf(__DATE__);
    printf("at");
    printf(__TIME__);
}
