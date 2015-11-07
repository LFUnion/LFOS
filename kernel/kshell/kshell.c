#include "kshell.h"
#include "kernel.h"

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
	print_raw(" >  ");
	
	char* inp = scanf();
	
	if (strcmp(inp, "HELP")) {
	    printf("");
	    printf("LFOS Kernel shell v0.1 experimental");
	    printf("-----------------------------------");
	    printf("REBOOT: 	Reboots the computer");
	    printf("ABORT:	Triggers an instant kernel panic");
	    printf("HALT:   	Halts the CPU");
	    printf("CLEAR:  	Clears the screen");
	    printf("SETUNAME:	Sets the user name");
	    printf("SETHNAME:	Sets the hostname");
	    printf("EXIT:	Returns to the debugging interface");
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
	} else if (strcmp(inp, "EXIT")) {
	    loop = 0;
	    break;
	} else {
	    print_raw("Unknown command: ");
	    printf(inp);
	}
    }
}
