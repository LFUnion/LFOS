#include "beeper.h"

void beep(int frequency) {
	uint8_t pic_conf = 0b10110110;  // Channel 2, AM:LO/HI, square waves, 16 bit
	outb(0x43, pic_conf);
	
	outb(0x42, (uint8_t) 1193180 / frequency);
	outb(0x42, (uint8_t) ((1193180 / frequency) >> 8));

	uint8_t pic_state = inb(0x61);
	outb(0x61, pic_state & 1 << 0); // Set bit 0 of the PIC state
}

void beep_stop() {
	uint8_t pic_state = inb(0x61);
	outb(0x61, pic_state | 1 << 0); // Clear bit 0 of the PIC state
}
