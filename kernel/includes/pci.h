#ifndef PCI_H
#define PCI_H

#include "pciio.h"
#include <stdint.h>

// DEFINES AND MAKROS

// Headerregister
#define VENDORIDREGISTER 0x00
#define DEVICEIDREGISTER 0x02
#define COMMANDREGISTER 0x04
#define STATUSREGISTER 0x06
#define REVISIONIDREGISTER 0x08
#define PROGIFREGISTER 0x09
#define SUBCLASSREGISTER 0x0A
#define CLASSCODEREGISTER 0x0B
#define CACHELINEREGISTER 0x0C
#define TIMERREGISTER 0x0D
#define HEADERREGISTER 0x0E
#define BISTREGISTER 0x0F

#define ISMULTIFUNC 0x80


// Unions and Structures

struct pci_header {
    uint32_t PciID;
    uint16_t VendorID;
    uint16_t DeviceID;
    uint8_t classcode;
    uint8_t subclass;
    uint8_t progif;
};

// Functions
void scan_pci();
uint32_t pci_check(uint8_t bus, uint8_t device);

// Functions for global use
uint8_t pci_test(uint8_t bus, uint8_t device, uint8_t functions);

// Do not declare inline else (linking error if you do so)
int8_t get_number_pci();

#endif
