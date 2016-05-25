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





//Unions and Structur

struct pci_header{
	uint32_t PciID;
    uint16_t VendorID;
    uint16_t DeviceID;
	uint8_t classcode;
	uint8_t subclass;
	uint8_t progif;
};

//functions

void scan_pci();

inline uint32_t pci_check(uint8_t bus, uint8_t device);

// functions for global use

uint8_t pci_test(bus, device, functions);

// not inline else (linking error)
int8_t get_number_pci();

#endif 
