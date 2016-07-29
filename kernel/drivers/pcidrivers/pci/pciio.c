
/*
LFOS, a simple operating system.
Copyright (C) 2016 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "portio.h"
#include <stdint.h>
#include "pciio.h"


// constant variables
const uint16_t pci_base = 0xCF8;


void out_pci_8 (uint32_t deviceAndVendorID, uint8_t pciRegister, uint8_t hex) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    outb(pci_base+4+(pciRegister & 0x03), hex);
}

uint8_t in_pci_8 (uint32_t deviceAndVendorID, uint8_t pciRegister) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    return (uint8_t)(inb(pci_base+4+(pciRegister & 0x03)));
}


void out_pci_16 (uint32_t deviceAndVendorID, uint8_t pciRegister,
                 uint16_t hex) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    outw(pci_base+4+(pciRegister & 0x02), hex);
}

uint16_t in_pci_16 (uint32_t deviceAndVendorID, uint8_t pciRegister) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    return (uint16_t)(inw(pci_base+4+(pciRegister & 0x02)));
}

void out_pci_32 (uint32_t deviceAndVendorID, uint8_t pciRegister,
                 uint32_t hex) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    outb(pci_base+4, hex);
}

uint32_t in_pci_32 (uint32_t deviceAndVendorID, uint8_t pciRegister) {
    outdw(pci_base,(ENABLEBIT | deviceAndVendorID | (pciRegister & 0xFC)));
    return (uint32_t)(indw(pci_base+4));
}
