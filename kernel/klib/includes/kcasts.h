#ifndef KCASTS_H
#define KCASTS_H

#include <stdint.h>

char * stringFromDouble(const double input, int8_t after);
int intFromString(char* restrict input);
unsigned int uintFromString(char* restrict input);
const char * itoa(int input);
const char * stringFromInt(int input);
int atoi(char* string);
char charFromDigit(int digit);

#endif /* KCASTS_H */
