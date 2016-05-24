#ifndef KIO_H
#define KIO_H

#include <stdint.h>

void printf(const char text[], ...);
char * scanf();
void scanf_new_prot(char * content, uint16_t size);
void printw(const char text[], ...);
void print_raw(const char text[]);
void printd(const int digit);
void clear();

#endif /* KIO_H */
