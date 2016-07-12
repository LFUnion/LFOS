#ifndef TAR_H
#define TAR_H

#include "stdint.h"
#include "klib.h"

typedef struct {
	char filename[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char time[12];
    char checksum[8];
    char type[1];
} tar_header_t;

int tar_read(char* filename, void* buffer, size_t size, size_t count, const tar_header_t* beginning);
int tar_get_size(char* filename, const tar_header_t* beginning);
char** tar_get_filenames(int* size, const tar_header_t* beginning);
tar_header_t* tar_get_header(char* filename, const tar_header_t* beginning);

#endif /* TAR_H */
