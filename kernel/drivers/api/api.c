#include "api.h"

const char const * pcidevicelist [0x11]={
"VGA-Compatible Device", "Mass Storage Controller", "Network Controller", "Display Controller",

"Multimedia Device", "Memory Controller", "Bridge Device", "Communications Device",

"System Peripheral", "Input Controller", "Docking Station",

"Co-Processor" , "USB", "Wireless Controller",

"FIFO" , "TAVD Controller", "Encryption/Decryption ",

"Data Acquisition/Signal Processing Controller "
};


const char const * pcidevicelistall [0x11][0x0A][0x05] = {

};

// A simple driver api

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
        
    } else if (input == 1){
        printf("KEYBOARD");
        keyboard_send();
     
    } else if (input == 2){
        printf("VGA");
        vga_send();
     
    } else if (input == 3){

    }

}

void driverfunctions (int input){

    if (input == 0){
        printf("ATA");
        ata_use(0);
        
    } else if (input == 1){
        printf("ATA");
        keyboard_use(0);
    
    } else if (input == 2){
        printf("ATA");
        vga_use(0);
    
    } else if (input == 3){
        
    }

}


void pci_device(){
    uint8_t max = get_number_pci();
    for(int c = 0; c<max; ++c){
        struct pci_header* pci_c = pci_api_data_return(c);
        readable_pci_device_names(max, max, max);
    }    
}

inline void readable_pci_device_names(uint8_t classcode, int8_t subclass, int8_t progif){
    print_raw("device functions: ");
    printf(pcidevicelist[classcode]);
}


int apiloop() {
    
    clear();
    
    alldriver();
    printf("Driver API Menu: Version 0.1");
    printf("For help: HELP");
    printf("To exit the API input EXIT\n");
    
    while (1){
        print_raw("command: ");
        char * input = scanf();
        strhighc(input);
        
        if (strcmp(input, "HELP")){
            printhelp();
        } else if (strcmp(input, "USE")){
            print_raw("Driver: ");
            char * input = scanf();
            if (strcmp(input, "ATA")){
                driverfunctions (0);
            }
            else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY")){
                driverfunctions (1);
            }
            else if (strcmp(input, "VGA")){
                driverfunctions (2);
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
            } else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY")){
                printdata(1);
            } else if (strcmp(input, "VGA")){
                printdata(2);
            } else if (strcmp(input, "SERIAL")){
                printdata(3);
            } else{
                printf("Not found");
            }
        }    
        else if (strcmp(input, "PCI")){
            pci_device();
        
        }
        else if (strcmp(input, "EXIT")){
            break;
        } else{
            printf("Wrong input");
        }
    }
    
    clear();
    return 0;
}
