#include "api.h"

const char const * pcidevicelist [0x12]= {
    "VGA-Compatible Device", "Mass Storage Controller", "Network Controller", "Display Controller",

    "Multimedia Device", "Memory Controller", "Bridge Device", "Communications Device",

    "System Peripheral", "Input Controller", "Docking Station",

    "Co-Processor" , "USB", "Wireless Controller",

    "FIFO" , "TAVD Controller", "Encryption/Decryption ",

    "Data Acquisition/Signal Processing Controller "
};


const char const * pci_vga [0x02] = {
    "VGA-Compatible device (excepted)", "VGA-Compatible device"
};

const char const * pci_mass_storage [0x09] = {
    "SCSI Bus Controller", "IDE Controller", "Floppy Disk Controller",
    "IPI Bus Controller ", "RAID Controller ", "ATA Controller",
    "Serial ATA", "Serial Attached SCSI", "Other Mass Storage Controller "
};

const char const * pci_network [0x08] = {
    "Ethernet Controller", "Token Ring Controller", "FDDI Controller",
    "ATM Controller", "ISDN Controller", "WorldFip Controller",
    "PICMG 2.14 Multi Computing", "Other Network Controller"
};

const char const * pci_display [0x04] = {
    "VGA-Compatible Controller", "XGA Controller",
    "3D Controller (Not VGA-Compatible)", "Other Display Controller"
};

const char const * pci_multimedia [0x04] = {
    "Video Device", "Audio Device", "Computer Telephony Device",
    "Other Multimedia Device"
};

const char const * pci_ram_flash [0x03] = {
    "RAM Controller", "FLASH Controller", "Other mempry Controller"
};

const char const * pci_bridge_network [0x0C] = {
    "Host Bridge", "ISA Bridge", "EISA Bridge",
    "MCA Bridge", "PCI-to-PCI Bridge", "PCMCIA Bridge",
    "NuBus Bridge", "CardBus Bridge", "RACEway Bridge",
    "PCI-to-PCI Bridge (Semi-Transparent)", "InfiniBrand-to-PCI Host Bridge", "Other Bridge Device"
};

const char const * pci_communication [0x07] = {
    "Generic XT-Compatible Serial Controller", "Parallel Port", "Multiport Serial Controller",
    "Generic Modem", "IEEE 488.1/2 (GPIB) Controller", "Smart Card",
    "Other Communications Device"
};

const char const * pci_system_peripheral [0x06] = {
    "Generic 8259 PIC", "Generic 8237 DMA Controller", "Generic 8254 System Timer",
    "Generic RTC Controller", "Generic PCI Hot-Plug Controller", "Other System Peripheral"

};

const char const * pci_input_device [0x06] = {
    "Keyboard Controller", "Digitizer", "Mouse Controller",
    "Scanner Controller", "Gameport Controller", "Other Input Controller"
};

const char const * pci_docking_station [0x02] = {
    "Generic Docking Station", "Other Docking Station"
};

const char const * pci_co_processor [0x07] = {
    "386 Processor", "486 Processor", "Pentium Processor",
    "Alpha Processor", "PowerPC Processor", "MIPS Processor",
    "Co-Processor"
};

const char const * pci_bus [0x0A] = {
    "IEEE 1394 Controller", "ACCESS.bus", "SSA",
    "USB", "Fibre Channel", "SMBus",
    "InfiniBand", "IPMI SMIC Interface", "SERCOS Interface Standard (IEC 61491)",
    "CANbus"
};

const char const * pci_wireless [0x08] = {
    "iRDA Compatible Controller", "Consumer IR Controller", "RF Controller",
    "Bluetooth Controller", "Broadband Controller", "Ethernet Controller (802.11a)",
    "Ethernet Controller (802.11b)", "Other Wireless Controller"
};

const char const * pci_fifo [0x02] = {
    "I20 Architecture", "Message FIFO"
};

const char const * pci_controller [0x04] = {
    "TV Controller", "Audio Controller", "Voice Controller",
    "Data Controller"
};

const char const * pci_enc_dec [0x03] = {
    "Network and Computing Encrpytion/Decryption", "Entertainment Encryption/Decryption", "Other Encryption/Decryption"

};

const char const * pci_signal_processing_controller [0x05] = {
    "DPIO Modules", "Performance Counters",
    "Communications Syncrhonization Plus Time and Frequency Test/Measurment",
    "Management Card",
    "Other Data Acquisition/Signal Processing Controller"
};

/*
const char const * pci_device_sub[0x11] = {
    pci_vga, pci_mass_storage,
    pci_network, pci_display,
    pci_multimedia, pci_ram_flash,
    pci_bridge_network, pci_communication,
    pci_system_peripheral, pci_input_device,
    pci_docking_station, pci_co_processor,
    pci_bus, pci_wireless,
    pci_fifo, pci_controller,
    pci_enc_dec, pci_signal_processing_controller

};
*/

const uint8_t length_pci_device_list[0x12] = {
    0x02, 0x09,
    0x08, 0x04,
    0x04, 0x03,
    0x0C, 0x07,
    0x06, 0x06,
    0x02, 0x07,
    0x0A, 0x08,
    0x02, 0x04,
    0x03, 0x05
};

// A simple driver api

void alldriver() {
    printf("All available drivers");
    printf("ATA");
    printf("KEYBOARD");
    printf("RFC");
    printf("SERIAL");
    printf("VGA\n");
    // request driver function
}

void printhelp() {
    printf("\nUSE and then the name of the driver");
    printf("USE has this options for the driver: read, write, ");
    printf("");
    printf("DATA and then the name of the driver: print the data of the driver");
    printf("HELP: print this menu");
    printf("DRIVERS: print all drivers");
    printf("EXIT: leaves the API or use\n");
}

void printdata(int input) {
    if (input == 0) {
        printf("ATA");
        ata_send();
    } else if (input == 1) {
        printf("KEYBOARD");
        keyboard_send();
    } else if (input == 2) {
        printf("VGA");
        vga_send();
    } else if (input == 3) {
    }
}

void driverfunctions (const int input) {
    if (input == 0) {
        printf("ATA");
        print_raw("Function: ");
        char * input = scanf();
        int input_i = atoi(input);

        if(input_i>0 && input_i<16)
            ata_use(input_i);
    } else if (input == 1) {
        printf("ATA");
        print_raw("Function: ");
        char * input = scanf();
        int input_i = atoi(input);

        if(input_i>0 && input_i<8)
            keyboard_use(input_i);
    } else if (input == 2) {
        printf("ATA");
        print_raw("Function: ");
        char * input = scanf();
        int input_i = atoi(input);

        if(input_i>0 && input_i<15)
            vga_use(input_i);
    } else if (input == 3) {
    } else
        printf("Not in driver list");
}


void pci_device() {
    uint8_t max = get_number_pci();

    for(int c = 0; c<max; ++c) {
        struct pci_header* pci_c = pci_api_data_return(c);
        readable_pci_device_names(pci_c->classcode, pci_c->subclass, pci_c->progif);
    }
}

void readable_pci_device_names(const uint8_t classcode, int8_t subclass,
                               const int8_t progif) {
    if(classcode>0x11)
        printf("Undefined PCI device group");

    print_raw("device functions: ");
    printf(pcidevicelist[classcode]);
    uint8_t length = length_pci_device_list[classcode-1];

    if(subclass>length)
        subclass = length - 1;

    //char * pci_list_c = pci_device_sub[classcode];
    //printf(pci_list_c[subclass]);

    //char * pci_list_s;

    if(classcode==0x00)
        printf(pci_vga[subclass]);
    else if(classcode==0x01)
        printf(pci_mass_storage[subclass]);
    else if(classcode==0x02)
        printf(pci_network[subclass]);
    else if(classcode==0x03)
        printf(pci_display[subclass]);
    else if(classcode==0x04)
        printf(pci_multimedia[subclass]);
    else if(classcode==0x05)
        printf(pci_ram_flash[subclass]);
    else if(classcode==0x06)
        printf(pci_bridge_network[subclass]);
    else if(classcode==0x07)
        printf(pci_communication[subclass]);
    else if(classcode==0x08)
        printf(pci_system_peripheral[subclass]);
    else if(classcode==0x09)
        printf(pci_input_device[subclass]);
    else if(classcode==0x0A)
        printf(pci_docking_station[subclass]);
    else if(classcode==0x0B)
        printf(pci_co_processor[subclass]);
    else if(classcode==0x0C)
        printf(pci_bus[subclass]);
    else if(classcode==0x0D)
        printf(pci_wireless[subclass]);
    else if(classcode==0x0E)
        printf(pci_fifo[subclass]);
    else if(classcode==0x0F)
        printf(pci_controller[subclass]);
    else if(classcode==0x10)
        printf(pci_enc_dec[subclass]);
    else if(classcode==0x11)
        printf(pci_signal_processing_controller[subclass]);

    print_raw("Number: ");
    print_raw(itoa(classcode));
    print_raw(" ");
    print_raw(itoa(subclass));
    print_raw(" ");
    printf(itoa(progif));
    printf("");
}


int apiloop() {
    clear();
    alldriver();
    printf("Driver API Menu: Version 0.2");
    printf("For help: HELP");
    printf("To exit the API input EXIT\n");

    while (1) {
        print_raw("command: ");
        char * input = scanf();
        strhighc(input);

        if (strcmp(input, "HELP"))
            printhelp();
        else if (strcmp(input, "USE")) {
            print_raw("Driver: ");
            char * input = scanf();

            if (strcmp(input, "ATA"))
                driverfunctions (0);
            else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY"))
                driverfunctions (1);
            else if (strcmp(input, "VGA"))
                driverfunctions (2);
            else if (strcmp(input, "SERIAL")) {
            } else
                printf("Not found");
        } else if (strcmp(input, "DATA")) {
            print_raw("Driver: ");
            char * input = scanf();

            if (strcmp(input, "ATA"))
                printdata(0);
            else if (strcmp(input, "KEYBOARD") || strcmp(input, "KEY"))
                printdata(1);
            else if (strcmp(input, "VGA"))
                printdata(2);
            else if (strcmp(input, "SERIAL"))
                printdata(3);
            else
                printf("Not found");
        } else if (strcmp(input, "PCI"))
            pci_device();
        else if (strcmp(input, "EXIT"))
            break;
        else
            printf("Wrong input");
    }

    clear();
    return 0;
}
