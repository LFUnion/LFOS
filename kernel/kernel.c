<<<<<<< HEAD
#include "vga.h"
=======
// Include the IO library, alternatively you can import the VGA driver (includes/vga.h)
#include "../clib/includes/stdio.h"
>>>>>>> 70e153d30670ab6dc5021a51042d0139f211ce9f

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
<<<<<<< HEAD
    kclear();
    klog("Welcome to LFOS!");
    klog("(C) 2015 by LFUnion");
    klog("");
    klog("Compiled");
    klog(__DATE__);
    klog("at");
    klog(__TIME__);
=======
    clear();
    printf("Welcome to LFOS!");
    printf("(C) 2015 by LFUnion");
    printf("");
    printf("Compiled");
    printf(__DATE__);
    printf("at");
    printf(__TIME__);
>>>>>>> 70e153d30670ab6dc5021a51042d0139f211ce9f
}
