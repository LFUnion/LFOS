#include "api.h"

// a simple driver api

void alldriver(){
	printf("All available Driver");
	printf("ATA");
	printf("KEYBOARD");
	printf("RFC");
	printf("SERIAL");
	printf("VGA\n");
	// request driver function
	
}

void printhelp(){
	printf("\nUSE and then the name of the driver");
	printf("USE has this options for the driver: read, write, ");
	printf("");
	printf("DATA and then the name of the driver: print the data of the driver");
	printf("HELP: print this menu");
	printf("DRIVERS: print all drivers");
	printf("EXIT: leaves the API or use\n");		
}

void printdata(int input){
			
			if (input == 0){
					printf("ATA");
					ata_send();
					
			}
			else if (input == 1){
				
			}
			else if (input == 2){
				
			}
			else if (input == 3){
				
			}	

}

void driverfunctions (int input){
			
			if (input == 0){
					printf("ATA");
					ata_use(0);
					
			}
			else if (input == 1){
				
			}
			else if (input == 2){
				
			}
			else if (input == 3){
				
			}	

}




int	apiloop() {
	
	clear();
	
	alldriver();
    printf("Driver API Menu: Version 0.1"");
	printf("For help: HELP");
	printf("To exit the API input EXIT\n");
	while (1){
		print_raw("command: ");
		char * input = scanf();
		if (strcmp(input, "HELP")){
			printhelp();
			
		}
		else if (strcmp(input, "USE")){
			print_raw("Driver: ");
			char * input = scanf();
			if (strcmp(input, "ATA")){
				driverfunctions (0);
			}
			else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY")){
			
			}
			else if (strcmp(input, "VGA")){
			
			}
			else if (strcmp(input, "SERIAL")){
			
			}
			else{
				printf("Not found");
			}
		}
		else if (strcmp(input, "DATA")){
			print_raw("Driver: ");
			char * input = scanf();
			if (strcmp(input, "ATA")){
				printdata(0);
			}
			else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY")){
				printdata(1);
			}
			else if (strcmp(input, "VGA")){
				printdata(2);
			}
			else if (strcmp(input, "SERIAL")){
				printdata(3);
			}
			else{
				printf("Not found");
			}
		}		
		else if (strcmp(input, "EXIT")){
			
			break;
		}
		else{
			printf("Wrong input");
		}
    }
    clear();
    return 0;
}
