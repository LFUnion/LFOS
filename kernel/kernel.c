#include "klib.h"

#include "cpu.h"
#include "keyboard.h"
#include "rtc.h"

#include "gdt.h"
#include "idt.h"

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

extern uint8_t rtc_second;

// Display head
void kmain(void) {
    clear();
    
    printf("[..] Loading IDT");
    load_idt();
    printf("[OK] IDT loaded");
    
    printf("[..] Detecting keyboards");
    if(kbd_detect() == 1) {
        printf("[OK] Keyboard detected");
    } else {
        printw("[!!] No keyboard detected");
    }
    printf("[..] Refreshing system time");
    rtc_refresh();
    printf("[OK] Time set");
    
    printf("");
    printw("Welcome to LFOS!");
    printw("(C) 2015 by LFUnion");
    printf("");
    printf("Compiled");
    printf(__DATE__);
    printf("at");
    printf(__TIME__);
    printf("");
    printf("[..] Halting CPU");
    cpu_halt();
    printw("[!!] COULD NOT HALT CPU");
}
