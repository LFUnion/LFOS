#ifndef BEEPER_H
#define BEEPER_H

#include <stdint.h>
#include "portio.h"

void beep(int frequency);
void beep_stop();

#endif /* BEEPER_H */
