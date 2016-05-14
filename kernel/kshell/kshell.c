/*!
 * \file
 * \brief KShell main
 *
 * This file contains the main kshell function
 */

#include "kshell.h"
#include "kernel.h"

/*!
 * \brief KShell entry
 * This function is the entry point for the KShell. It contains the main REP loop.
 */
void kshell_main(void) {
    int loop = 1;
    char* username = (char*)malloc(50 * sizeof(char));
    char* hostname = (char*)malloc(50 * sizeof(char));
    username = "USER";
    hostname = "LOCALHOST";

    while (loop) {
	print_raw(username);
	print_raw("@");
	print_raw(hostname);
	print_raw(" > ");
	
	char* inp = scanf();
	
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
	    printf("EXIT:       Returns to the debugging interface");
	    printf("");
	} else if (strcmp(inp, "REBOOT")) {
	    cpu_reset();
	} else if (strcmp(inp, "ABORT")) {
	    abort("Issued 'ABORT' in kshell_main");
	} else if (strcmp(inp, "CLEAR")) {
	    clear();
	} else if (strcmp(inp, "SETUNAME")) {
	    print_raw("New username: ");
	    username = scanf();
	} else if (strcmp(inp, "SETHNAME")) {
	    print_raw("New hostname: ");
	    hostname = scanf();
	} else if (strcmp(inp, "LS")) {
	    
	} else if (strcmp(inp, "RM")) {
	    print_raw("Filename > ");
	    const char* fn = scanf();
	    ufs_del_file(0, fn);
	} else if (strcmp(inp, "CAT")) {
	    print_raw("Filename > ");
	    const char* fn = scanf();
	    printf(read(fn));
	} else if (strcmp(inp, "EDIT")) {
	    print_raw("Filename > ");
	    const char* fn = scanf();
	    print_raw("Contents > ");
	    const char* ct = scanf();
	    const char* final = (const char*)malloc(216 * sizeof(uint16_t));
	    final = ct;
	    write(fn, final);
	}
	else if (strcmp(inp, "API")) {
	    apiloop();
	}
	else if (strcmp(inp, "EXIT")) {
	    loop = 0;
	    break;
	} else {
	    print_raw("Unknown command: ");
	    printf(inp);
	}
    }
}
