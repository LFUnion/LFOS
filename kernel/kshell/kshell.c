/*!
 * \file
 * \brief KShell main
 *
 * This file contains the main kshell function
 */

#include "kshell.h"
#include "kernel.h"
#include "tasks.h"
#include "api.h"

/*!
 * \brief KShell entry
 * This function is the entry point for the KShell. It contains the main REP loop.
 */
void kshell_main(void) {
    int loop = 1;
    char* username = (char*)malloc(50 * sizeof(char));
    char* hostname = (char*)malloc(50 * sizeof(char));
    username =  "USER";
    hostname = "LOCALHOST";

    while (loop) {
        print_raw(username);
        print_raw("@");
        print_raw(hostname);
        print_raw(" > ");
        char* inp = scanf();
        strhighc(inp);

        if (strcmp(inp, "HELP")) {
            printf("");
            printf("LFOS Kernel shell v0.1 experimental");
            printf("-----------------------------------");
            printf("REBOOT:     Reboots the computer");
            printf("ABORT:      Triggers an instant kernel panic");
            printf("HALT:       Halts the CPU");
            printf("CLEAR:      Clears the screen");
            printf("LS:         List all files");
            printf("RM:         Removes a file");
            printf("CAT:        Prints the contents of a file");
            printf("EDIT:       Edit a file");
            printf("SETUNAME:   Sets the user name");
            printf("SETHNAME:   Sets the hostname");
            printf("MMAP:       Print the memory map");
            printf("FREE:       Display free and used memory");
            printf("PS:         Display running processes");
            printf("EXIT:       Returns to the debugging interface");
            printf("");
        } else if (strcmp(inp, "REBOOT"))
            cpu_reset();
        else if (strcmp(inp, "ABORT"))
            abort("Issued 'ABORT' in kshell_main", NULL);
        else if (strcmp(inp, "CLEAR"))
            clear();
        else if (strcmp(inp, "SETUNAME")) {
            print_raw("New username: ");
            free(username);
            username = scanf();
        } else if (strcmp(inp, "SETHNAME")) {
            print_raw("New hostname: ");
            free(hostname);
            hostname = scanf();
        } else if (strcmp(inp, "LS")) {
        } else if (strcmp(inp, "RM")) {
            print_raw("Filename > ");
            char* fn = scanf();
            ufs_del_file(0, fn);
            free(fn);
        } else if (strcmp(inp, "CAT")) {
            print_raw("Filename > ");
            char* fn = scanf();
            printf(read(fn));
            free(fn);
        } else if (strcmp(inp, "EDIT")) {
            print_raw("Filename > ");
            char* fn = scanf();
            print_raw("Contents > ");
            char* ct = scanf();
            char* final = (char*)malloc(216 * sizeof(uint16_t));
            final = ct;
            write(fn, final);
            free(fn);
            free(final);
        } else if (strcmp(inp, "API")) {
            apiloop();
        } else if (strcmp(inp, "MMAP")) {
            for (int i = 0; i < (int)mmap_lenght; ++i) {
                print_raw("Address: ");
                print_raw(itoa(mmap[i].addr));
                print_raw("; Size: ");
                print_raw(itoa(mmap[i].len / 1024));
                print_raw(" kiB; Type: ");
                printf(itoa(mmap[i].type));
            }
        } else if (strcmp(inp, "FREE")) {
            print_raw("Free: ");
            print_raw(itoa(kmem_available() / 1024));
            print_raw(" kiB\nUsed: ");
            print_raw(itoa(kmem_used() / 1024));
            printf(" kiB");
        } else if (strcmp(inp, "PS")) {
            for (int i = 1; i <= (int)task_get_count(); ++i) {
                print_raw(itoa(i));
                print_raw(": ");

                if(task_get_id() == (uint32_t)i) {
                    printw(task_get_name((uint32_t)i));
                } else {
                    printf(task_get_name((uint32_t)i));
                }
            }
        } else if (strcmp(inp, "EXIT")) {
            loop = 0;
            break;
        } else {
            print_raw("Unknown command: ");
            printf(inp);
        }

        free(inp);
    }
}
