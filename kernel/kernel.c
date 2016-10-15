/*!
 * \file
 * \brief Kernel entry point
 *
 * This file contains the kernel entry point function
 */

/* Kernel Header */
#include "kernel.h"

/* Kernel C library */
#include "klib.h"

/* Kernel shell */
#include "kshell.h"

/* Drivers */
#include "cpu.h"
#include "keyboard.h"
#include "rtc.h"
#include "serial.h"
#include "pit.h"
#include "beeper.h"
#include "ata.h"
#include "acpi.h"
#include "vga.h"

//PCI and PCI Drivers
#include "pciio.h"
#include "pci.h"

/* Descriptor tables */
#include "gdt.h"
#include "idt.h"

/* Misc */
#include "exceptionhandler.h"
#include "pic.h"
#include "tasks.h"
#include "external/multiboot.h"
#include "tar.h"

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
void print_copyright();

/*!
 * \brief Kernel entry point
 *
 * This function gets called after boot/bootloader.asm set up the stack.
 * It then loads the required drivers, sets the system time, initializes the serial interfaces
 * and tries to detect a keyboard.
 */

const tar_header_t* tarhead;

/* Kernel entry point, called from boot/bootloader.asm */
void kmain(multiboot_info_t* mb_info) {
    const int mods_count = mb_info->mods_count;
    const multiboot_module_t* mod_start = (multiboot_module_t*)mb_info->mods_addr;
    tarhead = (tar_header_t*)mod_start->mod_start;
    clear();
    vga_disable_cursor();
    vga_set_position(0, 0);
    print_raw("[OK] Bootloader loaded ");
    print_raw(itoa(mods_count));
    printf(" modules");
    print_raw("[OK] Detected ");
    print_raw(cpu_getVendor());
    print_raw(" processor --> Number of Cores: ");
    printf(itoa(get_number_of_cores()));
    printf("[..] Loading GDT");
    load_gdt();
    printf("[OK] GDT loaded");
    printf("[..] Loading IDT");
    init_idt();
    printf("[OK] IDT loaded");
    find_acpi();
    printf("[..] Initializing PIC");
    pic_init();
    pit_init(PIT_FREQUENCY, 0);
    cpu_sti();
    printf("[OK] PIC initialized");
    printf("[..] Checking PCI");
    scan_pci();
    print_raw("[OK] PCI checked --> Number of PCI devices: ");
    printf(itoa(get_number_pci()));
    printf("[..] Initializing keyboard");

    if(kbd_detect() == 1 && kbd_init() == 1)
        printf("[OK] Keyboard initialized");
    else
        printw("[!!] Could not initialize keyboard");

    kbd_flush_buffer();
    //printf("[..] Refreshing system time");
    rtc_refresh();
    //printf("[OK] Time set");
    printf("[..] Initializing serial COM1");
    serial_init();
    send(0x50); // P
    send(0x49); // I
    send(0x4E); // N
    send(0x47); // G
    printf("[OK] COM1 ready");
    printf("[..] Checking initrd ...");

    if (mods_count < 1)
        printw("[!!] No initrd loaded");
    else {
        if (tar_get_header("lfos-initrd-version.txt", tarhead) == 0)
            printw("[!!] Initrd corrupt");
        else
            printf("[OK] Initrd found");
    }

    task_init((void*)kmain_task, "kernel");

    while (1) {}
}

void kmain_task(void) {
    task_init((void*)idle, "idle");
    printf("");
    printw("Welcome to LFOS!");
    printw("Copyright (C) 2015-2016  LFUnion");
    printf("");
    print_raw("You are using LFOS ");
    print_raw(LFOS_VERSION);
    print_raw(", compiled ");
    print_raw(__DATE__);
    print_raw(" at ");
    printf(__TIME__);
    printf("");
    printw("[##] Press any key to continue");
    kbd_flush_buffer();
    kbd_pull_key();
    clear();
    print_help();

    while (1) {
        kbd_flush_buffer();
        char resp = kbd_pull_char();
        char line[4] = "> ";
        line[2] = resp;
        line[3] = 0;
        printf(line);

        if (resp == 'R') {
            printf("[..] Rebooting");
            cpu_reset();
            printw("COULD NOT RESET CPU");
        } else if (resp == 'H') {
            printw("[!!] Halting CPU");
            cpu_cli();
            cpu_halt();
            printw("COULD NOT HALT CPU");
        } else if (resp == 'C')
            clear();
        else if (resp == 'S')
            kshell_main();
        else if (resp == 'A') {
            ata_init();
            printf("ATA: Initialized");
        } else if (resp == 'F') {
            ufs_init();
            ufs_format(0);
            uint16_t* data = (uint16_t*)malloc(216 * sizeof(uint16_t));

            for (int i=0; i <= 216; i++)
                data[i] = 1;

            writeb("test.txt", data);
            const uint16_t* op = readb("test.txt");

            for (int i=0; i <= 216; i++)
                print_raw((char*)itoa(op[i]));
        } else if (resp == '-')
            print_help();
        else if (resp == 'G')
            print_copyright();
    }
}

/*!
 * \brief Triggers a kernel panic
 *
 * This function triggers a kernel panic and forces the kernel to halt the CPU immediately.
 *
 * @param msg The error message to be displayed
 */
void abort(char* msg, registers_t* regs) {
    cpu_cli();

    int eax, ebx, ecx, edx, esp, eip;

    if (regs == NULL) {
        eax = ebx = ecx = edx = esp = eip = 0;
    } else {
        eax = regs->eax;
        ebx = regs->ebx;
        ecx = regs->ecx;
        edx = regs->edx;
        esp = regs->esp;
        eip = regs->eip;
    }

    clear();
    printw("LFOS kernel panic");
    printw("-----------------\n");
    printw(msg);
    printf("\n");
    printw("Debug information: \n");
    print_raw("Task: ");
    print_raw(itoa(task_get_id()));
    print_raw(" (");
    print_raw(task_get_name(task_get_id()));
    print_raw(")");
    printf("\n");

    if (regs != NULL) {
        print_raw("EAX: ");
        printf(itoa(eax));
        print_raw("EBX: ");
        printf(itoa(ebx));
        print_raw("ECX: ");
        printf(itoa(ecx));
        print_raw("EDX: ");
        printf(itoa(edx));
        print_raw("ESP: ");
        printf(itoa(esp));
        print_raw("EIP: ");
        printf(itoa(eip));
    }
    cpu_halt();
}

/*!
 * \brief Prints some help
 *
 * This function prints out help for the kernel debug interface
 */

void print_help() {
    printf(">>>> Kernel debug interface v0.2");
    printf(">>>> Commands:");
    printf(">>>> 'R': Restart");
    printf(">>>> 'H': Halt");
    printf(">>>> 'C': Clear screen");
    printf(">>>> 'S': Start the (experimental) shell");
    printf(">>>> 'A': Enable the ATA subsystem");
    printf(">>>> 'F': Automated test of uFS");
    printf(">>>> '=': Show this help");
    printf(">>>> 'G': Show the GPLv3 license notice");
}

void print_copyright() {
    printf("LFOS, a simple operating system.");
    printf("Copyright (C) 2015-2016 LFUnion");
    printf("");
    printf("This program is free software: you can redistribute it and/or modify");
    printf("it under the terms of the GNU General Public License as published by");
    printf("the Free Software Foundation, either version 3 of the License, or");
    printf("(at your option) any later version.");
    printf("");
    printf("This program is distributed in the hope that it will be useful,");
    printf("but WITHOUT ANY WARRANTY; without even the implied warranty of");
    printf("MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the");
    printf("GNU General Public License for more details.");
    printf("");
    printf("You should have received a copy of the GNU General Public License");
    printf("along with this program.  If not, see <http://www.gnu.org/licenses/>.");
}

void idle() {
    while (1) {
        //cpu_halt();
        asm volatile("int $0x20");
    }
}
