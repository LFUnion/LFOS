#include "kcom.h"
#include "serial.h"

#include "stdint.h"

void serial_writec(char c) {
    send((uint8_t)c);
}

char serial_readc() {
    char buf = (char)recv();
    return buf;
}
