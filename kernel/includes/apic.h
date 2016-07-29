#ifndef APIC_H
#define APIC_H

#include <stdint.h>
#include "klib.h"
#include "portio.h"
#include "acpi.h"

struct data_lapic {
    uint8_t type;
    uint8_t length;
    uint8_t id;
    uint8_t apicid;
    uint32_t flags;
} ;

struct data_ioapic {
    uint8_t type;
    uint8_t length;
    uint8_t ioapicid;
    uint8_t reserved;
    uint32_t ioapicaddress;
    uint32_t globalsysteminterruptbase;
} ;

struct data_iapic {
    uint8_t type;
    uint8_t length;
    uint8_t bus;
    uint8_t source;
    uint32_t interrupt;
    uint16_t flags;
};


int apictablemadt();
uint64_t get_apic_adress();
void apic_init();
void localapic_config();
void ioapic_config();
void writeapicreghex (uint8_t registern, uint32_t hex);
uint32_t readapicreg (uint8_t registern);
void pic_dis();

#endif
