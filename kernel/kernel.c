/* Kernel C library */
#include "klib.h"

/* Drivers */
#include "cpu.h"
#include "keyboard.h"
#include "rtc.h"
#include "serial.h"

/* Descriptor tables */
#include "gdt.h"
#include "idt.h"

#include "stdint.h"

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

/* Kernel entry point, called from boot/bootloader.asm */
void kmain(void) {
    clear();
    
    printf("[..] Loading GDT");
    load_gdt();
    printw("[!!] GDT loaded, but not flushed");
    
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
    
    printf("[..] Initializing serial COM1");
    serial_init();
    send(0x50); // P
    send(0x49); // I
    send(0x4E); // N
    send(0x47); // G
    printf("[OK] COM1 ready");
    
    printf("");
    printf("-- TIME HEADER START --");
    printd(get_second());
    printd(get_minute());
    printd(get_hour());
    printf("--  TIME HEADER END  --");
    
    char string[1];
    string[0] = charFromDigit(8);
    printf(string);
    const char** xxx = stringFromInt(324234);
    printf(*xxx);

    printf("");
    printw("Welcome to LFOS!");
    printw("(C) 2015 by LFUnion");
    printf("");
    printf("Compiled");
    printf(__DATE__);
    printf("at");
    printf(__TIME__);
    printf("");
    printf("[..] Sleeping 5 seconds");
    wait(5);
    printf("[OK] Process woke up");
    printf("[..] Halting CPU");
    cpu_halt();
    printw("[!!] COULD NOT HALT CPU");
}
