#include "memmanager.h"

// This is just a very simple MM to start with

void* crnt_addr = (void*)0x040000; // 4MB

void* malloc (size_t n) {
    void* return_addr = crnt_addr;
    crnt_addr += n;
    return return_addr;
}
