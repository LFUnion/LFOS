#include "serial.h"
#include "portio.h"

#include "stdint.h"
#include "klib.h"

static uint16_t com1 = 0x3F8; /* TODO: Read adresses from */
static uint16_t com2 = 0x2F8; /*       BIOS data area     */

void serial_init() {
    outb(com1+1, 0x00);
    outb(com1+3, 0x80);
    outb(com1+0, 0x03);
    outb(com1+1, 0x00);
    outb(com1+3, 0x03);
    outb(com1+2, 0xC7);
}

static int recv_buffer() {
    return (inb(com1+5) & 1);
}

static int send_buffer() {
    return (inb(com1+5) & 0x20);
}

void send (uint8_t chr) {
    while(send_buffer() == 0);
    outb(com1, (uint8_t)chr);
}

uint8_t recv () {
    while(recv_buffer() == 0);
    return inb(com1);
}