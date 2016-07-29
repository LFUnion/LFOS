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

#include "pciio.h"
#include "pci.h"
#include <stdint.h>
#include "driver_api.h"


const uint8_t maxnumberofpcidevices = 20;
struct pci_header pci_array[20];
uint8_t count_pci_device = 0;

void scan_pci() {
    uint8_t device, funccounter;
    device = 0;

    // Brute force

    for (uint16_t bus = 0; bus<0x100; ++bus) {
        for (device=0; device<0x20; ++device) {
            uint32_t funcnumber= pci_check(bus,device);

            for (funccounter = 0; funccounter<funcnumber; ++funccounter)
                pci_test(bus,device,funccounter);
        }
    }
}

uint32_t pci_check(uint8_t bus, uint8_t device) {
    uint32_t deviceAndVendorID = (bus << 16 | device <<11);
    uint8_t typofheader = in_pci_8(deviceAndVendorID, HEADERREGISTER);

    if (typofheader == ISMULTIFUNC)
        return 1;
    else
        return 8;
}


// Functions for global use

uint8_t pci_test(uint8_t bus, uint8_t device, uint8_t functions) {
    if (!(count_pci_device<maxnumberofpcidevices))
        return 1;

    uint32_t deviceAndVendorID = (bus<<16 | device<<11 | functions<<8);
    struct pci_header data;

    if (in_pci_16(deviceAndVendorID, VENDORIDREGISTER) == 0xFFFF)
        return 1;

    data.PciID = deviceAndVendorID;
    data.VendorID = in_pci_16(deviceAndVendorID, VENDORIDREGISTER);
    data.DeviceID = in_pci_16(deviceAndVendorID, DEVICEIDREGISTER);
    data.classcode = in_pci_8(deviceAndVendorID, CLASSCODEREGISTER);
    data.subclass = in_pci_8(deviceAndVendorID, SUBCLASSREGISTER);
    data.progif = in_pci_8(deviceAndVendorID, PROGIFREGISTER);
    pci_array[count_pci_device] = data;
    ++count_pci_device;
    return 0;
}

int8_t get_number_pci() {
    return count_pci_device;
}


// first available number is zero (0)

struct pci_header* pci_api_data_return(uint8_t number) {
    // struct pci_header* = pci_array + number;
    struct pci_header* pci_he = &(pci_array[number]);
    return pci_he;
}
