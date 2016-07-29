#include "ata.h"
#include "driver_api.h"

//api_declaration
struct driver_data_ata {
    struct driver_data datai;
    union function_data pfunc[15];

};


/* Constants */

const uint16_t ata_primary_baseport = 0x1F0;

/* Variables */


int ata_selected_drive = 2; // Not initialized
int ata_master_avail = 0;
int ata_slave_avail  = 0;

/* Functions */

uint8_t    ata_read_port (uint8_t port_offset) {
    return inb(ata_primary_baseport + port_offset);
}

void ata_write_port(uint8_t port_offset, uint8_t value) {
    outb(ata_primary_baseport + port_offset, value);
}


uint8_t ata_read_status_byte() {
    return ata_read_port(7);
}

int ata_read_status(int bit) {
    uint8_t val = ata_read_port(7);
    return (val & ( 1 << bit )) >> bit;
}


void ata_disable_interrupts() {
    outb(0x3F6, inb(0x3F6) | 1 << 1);
}


uint8_t ata_identify(int drive) {
    ata_select_drive(drive);
    ata_write_port(2, 0x00);
    ata_write_port(3, 0x00);
    ata_write_port(4, 0x00);
    ata_write_port(5, 0x00);
    ata_send_command(0xEC, drive);
    uint8_t ret = ata_read_status_byte();

    if (ret != 0) { // Drive exists
        while(ata_read_status(7)) {} // Wait for BSY to clear

        if (!ata_read_port(4) && !ata_read_port(5)) {
            while(!ata_read_status(3) &&
                    !ata_read_status(0)) {} // Wait for BSY or ERR to set

            if(!ata_read_status(0)) {
                for (int i=1; i<=256; i++)
                    ata_read_port(0);

                return ret;
            } else   // Not ATA
                return 0;
        } else {
            return 0;// Not ATA
        }
    }

    return ret;
}

void ata_reset() {
    outb(0x3F6, inb(0x3F6) | 1 << 2);
    outb(0x3F6, inb(0x3F6) & ~(1 << 2));
}

void ata_flush_cache(int drive) {
    ata_send_command(0xE7, drive);

    while(ata_read_status(7)) {} // Wait for BSY to clear
}

void ata_select_drive(int drive) {
    if (drive != ata_selected_drive) {
        if (drive == 0)   // Master
            ata_write_port(6, 0xA0);
        else        // Slave
            ata_write_port(6, 0xB0);

        ata_selected_drive = drive;

        for(int i=1; i<=4; i++)
            ata_read_status_byte(); // 400 ns delay, so the drive can respond
    }
}


void ata_send_command(uint8_t command, int drive) {
    while(ata_read_status(7)) {} // Wait for BSY to clear

    ata_select_drive(drive);
    ata_write_port(7, command);
}


/* These functions have to get called externally */

void ata_init() {
    if(ata_read_status_byte() == 0xFF)   // Floating bus
        abort("ATA: No drive connected to bus0");

    ata_master_avail = ata_identify(0);
    ata_slave_avail  = ata_identify(1);

    if(ata_master_avail + ata_slave_avail == 0)   // No ATA drive
        abort("ATA: No ATA drive connected to bus0");

    if(ata_master_avail)  {
        ata_select_drive(0);
        ata_disable_interrupts();
    }

    if(ata_slave_avail) {
        ata_select_drive(1);
        ata_disable_interrupts();
    }
}


uint16_t* ata_read_sector(int drive, uint32_t sector) {
    ata_write_port(6, 0xE0 | (drive << 4) | ((sector >> 24) & 0x0F));
    ata_write_port(1, 0x00);
    ata_write_port(2, 0x01);
    ata_write_port(3, (unsigned char) sector);
    ata_write_port(4, (unsigned char) (sector >> 8));
    ata_write_port(5, (unsigned char) (sector >> 16));
    ata_write_port(7, 0x20);
    uint16_t* buffer = (uint16_t*)malloc(1 * 256 * sizeof(uint16_t));

    for(int i=1; i<=4; i++)
        ata_read_status_byte(); // 400 ns delay, so the drive can respond

    int array_pos = 0;

    while(ata_read_status(3)) {
        for(int i=1; i<=256; i++) {
            uint16_t value;
            uint16_t port = 0x1F0;
            asm volatile ( "inw %1, %0" : "=a"(value) : "Nd"(port) );
            buffer[array_pos] = value;
            array_pos++;
        }

        for(int i=1; i<=4; i++)
            ata_read_status_byte(); // 400 ns delay, so the drive can respond
    }

    return buffer;
}

void ata_write_sector(int drive, uint32_t sector, uint16_t* data) {
    ata_write_port(6, 0xE0 | (drive << 4) | ((sector >> 24) & 0x0F));
    ata_write_port(1, 0x00);
    ata_write_port(2, 0x01);
    ata_write_port(3, (unsigned char) sector);
    ata_write_port(4, (unsigned char) (sector >> 8));
    ata_write_port(5, (unsigned char) (sector >> 16));
    ata_write_port(7, 0x30);

    for(int i=1; i<=4; i++)
        ata_read_status_byte(); // 400 ns delay, so the drive can respond

    int array_pos = 0;

    while(ata_read_status(3)) {
        for(int i=1; i<=256; i++) {
            uint16_t value = data[array_pos];
            uint16_t port = 0x1F0;
            asm volatile ( "outw %0, %1" : : "a"(value) , "Nd"(port) );
            array_pos++;
        }

        ata_write_port(7, 0xE7);

        for(int i=1; i<=4; i++)
            ata_read_status_byte(); // 400 ns delay, so the drive can respond
    }
}


uint16_t* ata_read_sectors(int drive, uint32_t base, int count) {
    ata_write_port(6, 0xE0 | (drive << 4) | ((base >> 24) & 0x0F));
    ata_write_port(1, 0x00);
    ata_write_port(2, (uint8_t) count);
    ata_write_port(3, (unsigned char) base);
    ata_write_port(4, (unsigned char) (base >> 8));
    ata_write_port(5, (unsigned char) (base >> 16));
    ata_write_port(7, 0x20);
    uint16_t* buffer = (uint16_t*)malloc(count * 256 * sizeof(uint16_t));

    for(int i=1; i<=4; i++)
        ata_read_status_byte(); // 400 ns delay, so the drive can respond

    int array_pos = 0;

    while(ata_read_status(3)) {
        for(int i=1; i<=256; i++) {
            uint16_t value;
            uint16_t port = 0x1F0;
            asm volatile ( "inw %1, %0" : "=a"(value) : "Nd"(port) );
            buffer[array_pos] = value;
            array_pos++;
        }

        for(int i=1; i<=4; i++)
            ata_read_status_byte(); // 400 ns delay, so the drive can respond
    }

    return buffer;
}

void ata_write_sectors(int drive, uint32_t base, int count, uint16_t* data) {
    ata_write_port(6, 0xE0 | (drive << 4) | ((base >> 24) & 0x0F));
    ata_write_port(1, 0x00);
    ata_write_port(2, (uint8_t)count);
    ata_write_port(3, (unsigned char) base);
    ata_write_port(4, (unsigned char) (base >> 8));
    ata_write_port(5, (unsigned char) (base >> 16));
    ata_write_port(7, 0x30);

    for(int i=1; i<=4; i++)
        ata_read_status_byte(); // 400 ns delay, so the drive can respond

    int array_pos = 0;

    while(ata_read_status(3)) {
        for(int i=1; i<=256; i++) {
            uint16_t value = data[array_pos];
            uint16_t port = 0x1F0;
            asm volatile ( "outw %0, %1" : : "a"(value) , "Nd"(port) );
            array_pos++;
        }

        ata_write_port(7, 0xE7);

        for(int i=1; i<=4; i++)
            ata_read_status_byte(); // 400 ns delay, so the drive can respond
    }
}

// API data

const struct driver_data_ata ata_api = {
    .datai.driver_number=ATA,
    .datai.number_of_functions=15,
    .datai.driver_priority=1,
    //.datai.driver_description=(char *)malloc(sizeof(char) *100),
    .datai.driver_description="ATA Driver: -communication with hard disk",
    .pfunc[0].func_8_8 = &ata_read_port,
    .pfunc[1].func_v_8_8 = &ata_write_port,
    .pfunc[2].func_8 = &ata_read_status_byte,
    .pfunc[3].func_i_i = &ata_read_status,
    .pfunc[4].func_v = &ata_disable_interrupts,
    .pfunc[5].func_8_i = &ata_identify,
    .pfunc[6].func_v = &ata_reset,
    .pfunc[7].func_v_i = &ata_flush_cache,
    .pfunc[8].func_v_i = &ata_select_drive,
    .pfunc[9].func_v_8_i = &ata_send_command,
    .pfunc[10].func_v = &ata_init,
    .pfunc[11].func_16_i_32 = &ata_read_sector,
    .pfunc[12].func_v_i_32_16p = &ata_write_sector,
    .pfunc[13].func_16_i_32_i =ata_read_sectors,
    .pfunc[14].func_v_i_32_i_16p = &ata_write_sectors
};



void ata_send() {
    print_raw("Number of functions: ");
    printf(stringFromInt(ata_api.datai.number_of_functions));
    print_raw("Priority: ");
    printf(stringFromInt(ata_api.datai.driver_priority));
    printf(ata_api.datai.driver_description);
}

void ata_use(const int func) {
    if (func ==1) {
        printf("Read Ports: ");
        int count = 0;

        while (count<8) {
            int ret = (*ata_api.pfunc[0].func_8_8) (count);
            print_raw("ATA-Port ");
            print_raw(stringFromInt(count));
            print_raw(": ");
            printf(stringFromInt(ret));
            ++count;
        }
    } else if (func ==2) {
        print_raw("Write Ports: ");
        char* port = scanf();
        int port_i = uintFromString(port);
        char* value = scanf();
        int value_i = uintFromString(value);
        (*ata_api.pfunc[1].func_v_8_8) (port, value);
        free(port);
        free(value);
    } else if (func ==3) {
        print_raw("Print status byte: ");
        int i = (*ata_api.pfunc[2].func_8) ();
        printf(stringFromInt(i));
    } else if (func ==4) {
        printf("Read status");
        print_raw("Input Bit: ");
        char* value = scanf();
        int value_i = uintFromString(value);
        int i = ata_api.pfunc[3].func_i_i (value_i);
        printf(stringFromInt(i));
        free(value);
    } else if(func == 5) {
        printf("Disabble Interrupts");
        ata_api.pfunc[4].func_v ();
    } else if(func == 6) {
        print_raw("Select drive: ");
        char * value = scanf();
        int value_i = uintFromString(value);
        uint8_t i = ata_api.pfunc[5].func_8_i (value_i);
        printf(stringFromInt(i));
        free(value);
    } else if(func == 7) {
        printf("ATA reset");
        ata_api.pfunc[6].func_v ();
    } else if(func == 8) {
        printf("Flush Cache");
        print_raw("Select Drive: ");
        char * value = scanf();
        int value_i = uintFromString(value);
        ata_api.pfunc[7].func_v_i (value_i);
        free(value);
    } else if(func == 9) {
        print_raw("Select Drive: ");
        char * value = scanf();
        int value_i = uintFromString(value);
        ata_api.pfunc[8].func_v_i (value_i);
        free(value);
    } else if (func == 10) {
        char * command = scanf();
        int command_i = uintFromString(command);
        char * drive = scanf();
        int drive_i = uintFromString(drive);
        ata_api.pfunc[9].func_v_8_i (command_i, drive_i);
        free(command);
        free(drive);
    } else if (func == 11) {
        printf("ATA init");
        ata_api.pfunc[10].func_v ();
    } else if (func == 12) {
        print_raw("Select Drive: ");
        char * drive = scanf();
        int drive_i = uintFromString(drive);
        print_raw("Select sector: ");
        char * sector = scanf();
        int sector_i = uintFromString(sector);
        uint16_t* startadress = ata_api.pfunc[11].func_16_i_32 (drive_i, sector_i);
        const uint16_t* endadress = startadress + 256;

        while(endadress>startadress) {
            printf(stringFromInt(*startadress));
            ++startadress;
        }

        free(drive);
        free(drive);
    } else if (func == 13) {
        print_raw("Select Drive: ");
        char * drive = scanf();
        int drive_i = uintFromString(drive);
        print_raw("Select (start) sector: ");
        char * sector = scanf();
        int sector_i = uintFromString(sector);
        print_raw("Data: ");
        char * data = scanf();
        uint16_t data_i[256];

        for(unsigned int c = 0; c<256; ++c ) {
            char * data = scanf();
            data_i[c] = uintFromString(data);
            free(data);
        }

        ata_api.pfunc[12].func_v_i_32_16p (drive_i, sector_i, data_i);
        free(sector);
        free(drive);
    } else if (func == 14) {
        print_raw("Select Drive: ");
        char * drive = scanf();
        int drive_i = uintFromString(drive);
        print_raw("Select sector: ");
        char * sector = scanf();
        int sector_i = uintFromString(sector);
        print_raw("Number of sectors: ");
        char * count = scanf();
        int count_i = uintFromString(count);
        uint16_t* startadress = ata_api.pfunc[13].func_16_i_32_i (drive_i, sector_i,
                                count_i);
        const uint16_t* endadress = startadress + count_i*256;

        while(startadress < endadress) {
            printf(stringFromInt(*startadress));
            ++startadress;
        }

        free(count);
        free(sector);
        free(drive);
    } else if (func == 15) {
        print_raw("Select Drive: ");
        char * drive = scanf();
        int drive_i = uintFromString(drive);
        print_raw("Select (start) sector: ");
        char * sector = scanf();
        int sector_i = uintFromString(sector);
        print_raw("Number of sectors: ");
        char * count = scanf();
        int count_i = uintFromString(count);
        uint16_t data_i[count_i*256];
        printf("Data:");

        for (int i = 0; i<count_i; ++i) {
            for(unsigned int c = 0; c<256; ++c ) {
                char * data = scanf();
                data_i[(i *256) +c] = uintFromString(data);
                free(data);
            }
        }

        ata_api.pfunc[14].func_v_i_32_i_16p (drive_i, sector_i, count_i, data_i);
        free(count);
        free(sector);
        free(drive);
    }
}
