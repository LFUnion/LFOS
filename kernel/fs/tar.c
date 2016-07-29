#include "tar.h"

int tar_read(char* filename, void* buffer, size_t size, size_t count,
             const tar_header_t* beginning) {
    tar_header_t* header = tar_get_header(filename, beginning);
    void* content = (void*)((uint8_t*)header + 512);

    if (header == 0)
        return -1;

    memcpy(content, buffer, size*count);
    return 0;
}

int tar_get_size(char* filename, const tar_header_t* beginning) {
    return atoi(tar_get_header(filename, beginning)->size);
}

char** tar_get_filenames(int* size, const tar_header_t* beginning) {
    *size = 0;
    tar_header_t* header = (tar_header_t*)beginning;

    while (1) {
        if (strlen(header->filename) == 0)
            break;
        else {
            header = (tar_header_t*)((uint8_t*)header + 512 + atoi(header->size));
            *size += 1;
        }
    }

    char** filenames = (char**)malloc(*size*sizeof(char*));
    header = (tar_header_t*)beginning;

    for (int i = 0; i < *size; i++) {
        filenames[i] = header->filename;
        header = (tar_header_t*)((uint8_t*)header + 512 + atoi(header->size));
    }

    return filenames;
}

tar_header_t* tar_get_header(char* filename, const tar_header_t* beginning) {
    tar_header_t* header = (tar_header_t*)beginning;

    while (1) {
        if (strlen(header->filename) == 0)
            return (tar_header_t*)0;
        else if (strcmp(header->filename, filename))
            break;
        else
            header = (tar_header_t*)((uint8_t*)header + 512 + atoi(header->size));
    }

    return header;
}
