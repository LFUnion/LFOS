#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "klib.h"
#include "portio.h"

#include "stdint.h"

uint8_t kbd_send(uint8_t command);
int kbd_reset();
int kbd_flush_buffer();
int kbd_init();
int kbd_detect();

uint8_t kbd_pull_key();
char kbd_pull_char();

#endif /* KEYBOARD_H */
