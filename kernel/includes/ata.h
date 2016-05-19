#ifndef ATA_H
#define ATA_H

#include <stdint.h>

#include "kernel.h"
#include "klib.h"
#include "portio.h"

/* Functions */

uint8_t    ata_read_port (uint8_t port_offset);
void    ata_write_port(uint8_t port_offset, uint8_t value);

uint8_t ata_read_status_byte();
int     ata_read_status(int bit);

void    ata_disable_interrupts();

uint8_t    ata_identify(int drive);

void     ata_reset();
void     ata_flush_cache(int drive);
void     ata_select_drive(int drive);

void     ata_send_command(uint8_t command, int drive);


/* Functions which must be called outside of ata.c */

void     ata_init();

uint16_t* ata_read_sector(int drive, uint32_t sector);
void    ata_write_sector(int drive, uint32_t sector, uint16_t* data);

uint16_t* ata_read_sectors(int drive, uint32_t base, int count);
void      ata_write_sectors(int drive, uint32_t base, int count, uint16_t* data);

#endif /* ATA_H */
