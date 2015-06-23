#ifndef KEYBOARD_H
#define KEYBOARD_H

uint8_t kbd_send(uint8_t command);
int kbd_reset();
int kbd_init();
int kbd_detect();

#endif /* KEYBOARD_H */