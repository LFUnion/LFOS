#ifndef KCASTS_H
#define KCASTS_H

#include <stdint.h>

char * stringFromDouble(const double input, int8_t after);
const char * itoa(int input);
const char * stringFromInt(int input);
char charFromDigit(int digit);

#endif /* KCASTS_H */
