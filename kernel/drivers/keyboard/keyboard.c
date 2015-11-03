#include "keyboard.h"

// PS/2 controller port: 0x64
// Keyboard port: 	 0x60

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

uint8_t kbd_pull_key() {
    while (((inb(0x64) >> 0)  & 0x01) == 0) {} // Wait until there is something in the buffer
    return inb(inb(0x60)); // Read the buffer
}

int kbd_reset() {
    uint8_t resp = kbd_send(0xFF); // Sending reset command
    if(resp == 0xFA) { // 0xFA = Reset done
        return 1;
    } else {
        return 0;
    }
}

int kbd_flush_buffer() {
    outb(0x64, 0xAD); // Disable PS/2 (1)
    while ((inb(0x64) >> 0)  & 0x01) {
    	inb(0x60);    // Flush   buffer
    }
    outb(0x64, 0xAE); // Enable  PS/2 (1)
    return 1;
}

int kbd_init() {
    if(kbd_reset() == 0) {
	return 0; // Reset failed
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

