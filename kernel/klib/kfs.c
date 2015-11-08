#include "kfs.h"

void write(const char* filename, const char* data) {
    ufs_write(0, filename, data);
}

const char* read(const char* filename) {
    return ufs_read(0, filename);
}


void writeb(const char* filename, const uint16_t* data) {
    ufs_write_b(0, filename, data);
}

const uint16_t* readb(const char* filename) {
    return ufs_read_b(0, filename);
}
