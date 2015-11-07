#include "ata.h"

/* Constants */

const uint16_t ata_primary_baseport = 0x1F0; 

/* Variables */

int ata_selected_drive = 2; // Not initialized
int ata_master_avail = 0;
int ata_slave_avail  = 0;

/* Functions */

uint8_t	ata_read_port (uint8_t port_offset) {
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
	if (!ata_read_port(4) && ata_read_port(5)) {
	    while(!ata_read_status(3) && !ata_read_status(0)) {} // Wait for BSY or ERR to set
	    if(!ata_read_status(0)) {
		for (int i=1; i<=256; i++) {ata_read_port(0);}
	    } else { // Not ATA
		return 0;
	    }
	} else {
	    return 0;// Not ATA
	}
    }
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
	if (drive == 0) { // Master
	    ata_write_port(6, 0xA0);
	} else {	  // Slave
	    ata_write_port(6, 0xB0);
	}
	
	ata_selected_drive = drive;
	for(int i=1;i<=4;i++) {ata_read_status_byte();} // 400 ns delay, so the drive can respond
    }
}


void ata_send_command(uint8_t command, int drive) {
    while(ata_read_status(7)) {} // Wait for BSY to clear
    ata_select_drive(drive);
    ata_write_port(7, command);
}




void ata_init() {
    if(ata_read_status_byte() == 0xFF) { // Floating bus
	abort("ATA: No drive connected to bus0");
    }

    ata_master_avail = ata_identify(0);
    ata_slave_avail  = ata_identify(1);

    if(ata_master_avail + ata_slave_avail == 0) { // No ATA drive
	abort("ATA: No ATA drive connected to bus0");
    }

    if(ata_master_avail)  {
	ata_select_drive(0);
	ata_disable_interrupts();
    } if(ata_slave_avail) {
	ata_select_drive(1);
	ata_disable_interrupts();
    }
}


uint16_t ata_read_sector(int drive, int sector) {
     
}

void ata_write_sector(int drive, int sector, int data) {

}


uint16_t* ata_read_sectors(int drive, int base, int count) {

}

void ata_write_sectors(int drive, int base, int count, int* data) {

}
