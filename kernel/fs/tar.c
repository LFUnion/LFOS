#include "tar.h"

int tar_read(char* filename, void* buffer, size_t size, size_t count, tar_header_t* beginning) {
	tar_header_t* header = tar_get_header(filename, beginning);
	void* content = (void*)((uint8_t*)header + 512);

	if (header == 0)
		return -1;

	memcpy(content, buffer, size*count);
	return 0;
}

int tar_get_size(char* filename, tar_header_t* beginning) {
	return atoi(tar_get_header(filename, beginning)->size);
}

tar_header_t* tar_get_header(char* filename, tar_header_t* beginning) {
	while (1) {
		if (strlen(beginning->filename) == 0)
			return (tar_header_t*)0;
		else if (strcmp(beginning->filename, filename))
			break;
		else
			beginning = (tar_header_t*)((uint8_t*)beginning + 512 + atoi(beginning->size));
	}
	return beginning;
}
