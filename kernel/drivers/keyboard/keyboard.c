#include "stdint.h"
#include "klib.h"
#include "keyboard.h"
#include "portio.h"

// Keyboard controller port: 0x60

uint8_t kbd_send(uint8_t command) {
    int resend = 1;
    while(resend == 1) {
        outb(0x60, command);
        uint8_t ret = inb(0x60);
        if(ret == 0xFE) {
            resend = 1;
            continue;
        } else {
            if(ret == 0xFA) {
                resend = 0;
                return 0xFA;
            } else {
                resend = 0;
                return ret;
            }
        }
    }
    printw("[EE] EXCEPTION: Reached end of keyboard output buffer ");
    return 0;
}

//uint8_t kbd_sread(uint8_t) {}

int kbd_reset() {
    uint8_t resp = kbd_send(0xFF); // Sending reset command
    if(resp == 0xAA) { // 0xAA = Self test passed
        return 1;
    } else {
        return 0;
    }
}
int kbd_init() {
    uint8_t resp = kbd_send(0xAA); // Perform selftest
    if(resp != 0x55) {
        return 0; // Return 0 if selftest failed
    }
    kbd_send(0xF6); // Load defaults
    return 1;
}

int kbd_detect() {
    outb(0x60, 0xEE); // Sending echo command
    uint8_t response = inb(0x60); // Waiting for response
    if(response == 0xEE || response == 0xFE) {
        return 1;
    } else {
        return 0;
    }
}

