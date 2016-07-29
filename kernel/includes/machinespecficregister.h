#ifndef MACHINESPECFICREGISTER_H
#define MACHINESPECFICREGISTER_H

#include <stdint.h>

uint64_t crdmsr(uint32_t mregister);
void cwrmsr(uint32_t mregister, uint64_t input);

#endif
