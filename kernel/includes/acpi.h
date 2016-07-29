#ifndef ACPI_H
#define ACPI_H

#include "klib.h"
#include <stdint.h>

#define RSD_PTR 0
#define RSDT 1
#define XSDT 2
#define MADT 3
#define FACP 4
#define MADT2 5

struct data_rsdp {
    char signature[8];
    uint8_t checksum;
    uint8_t oemid[6];
    uint8_t revision;
    uint32_t* ptrrsdt;
    uint32_t length;
    uint64_t* ptrxsdt;
    uint8_t exchecksum;
    uint8_t reserved[3];

};

struct data_rsdt {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint64_t oemtableid;
    uint32_t oemrevision;
    uint32_t creatorid;
    uint32_t creatorrevision;
    uint32_t othertable[5];
};

struct data_xsdt {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint64_t oemtableid;
    uint32_t oemrevision;
    uint32_t creatorid;
    uint32_t creatorrevision;
    uint32_t othertable[5];

};

struct data_madt {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint64_t oemtableid;
    uint32_t oemrevision;
    uint32_t creatorid;
    uint32_t creatorrevision;
    uint32_t localapicadr;
    uint32_t flags;
};

struct data_racp {
    char signature[4];
    uint32_t length;
    uint8_t revision;
    uint8_t checksum;
    uint8_t oemid[6];
    uint64_t oemtableid;
    uint32_t oemrevision;
    uint32_t creatorid;
    uint32_t creatorrevision;
    uint32_t firmwareControl;
    uint32_t dsdt;

};

struct data_madt* first_digit_of_madt;
uint8_t acpi_flags;

void find_acpi();
uint8_t search_table(uint8_t i, uint32_t* first_digit);
void configuration_of_tables(uint8_t c, uint32_t first_digit);

#endif
