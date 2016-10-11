#ifndef KCASTS_H
#define KCASTS_H

#include <stdint.h>

char * dtoa(const double input, int8_t after);
unsigned int atoui(char* restrict input);
const char * itoa(int input);
int atoi(char* string);
char dtoc(int digit);

#endif /* KCASTS_H */
