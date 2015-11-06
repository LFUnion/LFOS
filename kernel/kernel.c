/* Kernel C library */
#include "klib.h"

/* Kernel shell */
#include "kshell.h"

/* Drivers */
#include "cpu.h"
#include "keyboard.h"
#include "rtc.h"
#include "serial.h"
#include "beeper.h"

/* Descriptor tables */
#include "gdt.h"
#include "idt.h"

/* Misc */
#include "exceptionhandler.h"

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

void print_help();

/* Kernel entry point, called from boot/bootloader.asm */
void kmain(void) {
    clear();
    

    // I just realised: GRUB is loading the GDT for us ...
    //printf("[..] Loading GDT");
    //load_gdt();
    //printw("[!!] GDT loaded, but not flushed");
    
    printf("[..] Loading IDT");
    init_idt();
    register_exception_handlers();
    load_idt();
    printf("[OK] IDT loaded");
    
    printf("[..] Initializing keyboard");
    if(kbd_detect() == 1 && kbd_init() == 1) {
        printf("[OK] Keyboard initialized");
    } else {
        printw("[!!] Could not initialize keyboard");
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

    printf("");
    printw("Welcome to LFOS!");
    printw("(C) 2015 by LFUnion");
    printf("");
    print_raw("Compiled ");
    print_raw(__DATE__);
    print_raw(" at ");
    printf(__TIME__);
    printf("");

    wait(1);
    printw("[##] Press any key to continue");
    kbd_flush_buffer();
    kbd_pull_key();
    clear();

    print_help();
    while (1) {

	kbd_flush_buffer();
	char resp = kbd_pull_char();
        char line[3] = "> ";
        line[2] = resp;
	printf(line);

	if (resp == 'R') {
	    printf("[..] Rebooting");
	    cpu_reset();
	    printw("COULD NOT RESET CPU");
	} else if (resp == 'H') {
            printw("[!!] Halting CPU");
	    cpu_halt();
	    printw("COULD NOT HALT CPU");
	} else if (resp == 'C') {
	    clear();
	} else if (resp == 'S') {
	    kshell_main();
	} else if (resp == '-') {
	    print_help();
	}
    }
}

void print_help() {
    printf(">>>> Kernel debug interface v0.2");
    printf(">>>> Commands:");
    printf(">>>> 'R': Restart");
    printf(">>>> 'H': Halt");
    printf(">>>> 'C': Clear screen");
    printf(">>>> 'S': Start the (experimental) shell");
    printf(">>>> '=': Show this help");
}
