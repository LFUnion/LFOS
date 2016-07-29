#ifndef PCIIO_H
#define PCIIO_H

#include "portio.h"
#include <stdint.h>


// DEFINES AND MAKROS
#define ENABLEBIT (uint32_t)0x80000000


//#define CONFIG_PCIADDR(BUS, HEADER) (ENABLEBIT | BUS | (HEADER & 0xFC))

//functions

void out_pci_8 (uint32_t deviceAndVendorID, uint8_t pciRegister, uint8_t hex);

uint8_t in_pci_8 (uint32_t deviceAndVendorID, uint8_t pciRegister);

void out_pci_16 (uint32_t deviceAndVendorID, uint8_t pciRegister, uint16_t hex);

uint16_t in_pci_16 (uint32_t deviceAndVendorID, uint8_t pciRegister);

void out_pci_32 (uint32_t deviceAndVendorID, uint8_t pciRegister, uint32_t hex);

uint32_t in_pci_32 (uint32_t deviceAndVendorID, uint8_t pciRegister);


#endif
