#ifndef KFS_H
#define KFS_H

#include <stdint.h>

#include "ufs.h"
#include "klib.h"

void         write(const char* filename, const char* data);
const char*     read(const char* filename);

void         writeb(const char* filename, const uint16_t* data);
const uint16_t* readb(const char* filename);

#endif /* KFS_H */
