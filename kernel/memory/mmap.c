#include "mmap.h"

void initialize_mmap(multiboot_info_t* mb_info) {
    mmap_lenght = mb_info->mmap_length / 24;

    multiboot_memory_map_t* current_entry = (multiboot_memory_map_t*)multiboot_info.mmap_addr;

    for (int i = 0; i < (int)mmap_lenght; ++i) {
        mmap[i] = *current_entry;
        current_entry++;
    }
}
