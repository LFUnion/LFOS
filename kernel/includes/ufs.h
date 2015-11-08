#ifndef UFS_H
#define UFS_H

#include <stdint.h>

#include "ata.h"
#include "klib.h"

void		ufs_init();
void 		ufs_format(int disk);

uint16_t* 	ufs_get_super(int disk);
void		ufs_set_super(int disk, uint16_t* data);

uint32_t	ufs_get_sector(int disk, int fid);
void 		ufs_set_sector(int disk, int fid);

uint16_t*	ufs_get_data(int disk, uint32_t sector);
void 		ufs_set_data(int disk, uint32_t sector, uint16_t* data);

const char* 	ufs_get_filename(int disk, uint32_t sector);
void 		ufs_set_filename(int disk, uint32_t sector, const char* filename);

int		ufs_get_last_sector(int disk);
int 		ufs_get_last_fid(int disk);

int		ufs_get_fid(int disk, const char* filename);
int		ufs_sector2fid(int disk, uint32_t sector);


void 		ufs_write(int disk, const char* filename, const char* data);
const char* 	ufs_read(int disk, const char* filename);

void 		ufs_write_b(int disk, const char* filename, const uint16_t* data);
const uint16_t* ufs_read_b(int disk, const char* filename);

#endif /* UFS_H */
