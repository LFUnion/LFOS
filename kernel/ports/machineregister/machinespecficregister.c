#include "machinespecficregister.h"


uint64_t crdmsr(uint32_t mregister) {
    uint64_t rvalue;
    uint32_t part1 , part2;
    asm volatile("rdmsr"
                 :"=a" (part1), "=d" (part2)
                 :"c" (mregister)
                );
    rvalue = part1 | (uint64_t)part2<<32;
    return rvalue;
}

void cwrmsr(uint32_t mregister, uint64_t input) {
    uint32_t part1 = input & 0xFFFFFFFF;
    uint32_t part2 = input >> 32;
    asm volatile("rdmsr"
                 :
                 : "a" (part1), "c" (mregister), "d" (part2)
                );
}
