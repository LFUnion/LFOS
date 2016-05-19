#include "ufs.h"

uint16_t* superblock0;
uint16_t* superblock1;

void ufs_init(int disk) {
    if (disk == 0) {
    superblock0 = ata_read_sector(0, 0x0);
    } else {
    superblock1 = ata_read_sector(1, 0x0);
    }
}

void ufs_format(int disk) {
    if (disk == 0) {

    superblock0[0] = 0x70B1;
    superblock0[1] = 0x0001;

    for(int i = 2; i <= 255; i++) {
        superblock0[i] = 0x0;
    }

    ata_write_sector(0, 0x0, superblock0);

    } else {

    superblock0[0] = 0x70B1;
    superblock0[1] = 0x0001;

    for(int i = 0; i <= 255; i++) {
        superblock1[i] = 0x0;
    }

    ata_write_sector(0, 0x0, superblock1);

    }
}

uint16_t* ufs_get_super(int disk) {
    if (disk == 0) {
    return superblock0;
    } else {
    return superblock1;
    }
}

void ufs_set_super(int disk, uint16_t* data) {
    if (disk == 0) {
    ata_write_sector(0, 0x0, data);
    superblock0 = data;
    } else {
    ata_write_sector(1, 0x0, data);
    superblock1 = data;
    }
}


uint32_t ufs_get_sector(int disk, int fid) {
    uint16_t* sb = ufs_get_super(disk);
    for (int i = 2; i <= 255; i++) {
    if (sb[i] == (uint16_t)fid) {return i-1;}
    }
    return 0;
}

void ufs_set_sector(int disk, int fid) {
    uint16_t* sb = ufs_get_super(disk);
    for (int i = 2; i <= 255; i++) {
    if (sb[i] == (uint16_t)0) {sb[i] = fid; break;}
    }
    ufs_set_super(disk, sb);
}


void ufs_del_sector(int disk, int fid) {
    uint16_t* sb = ufs_get_super(disk);
    for (int i = 2; i <= 255; i++) {
    if (sb[i] == (uint16_t)fid) {sb[i] = 0; break;}
    }
    ufs_set_super(disk, sb);
}


uint16_t* ufs_get_data(int disk, uint32_t sector) {
    uint16_t* raw = ata_read_sector(disk, sector);
    uint16_t* data = (uint16_t*)malloc(216 * sizeof(uint16_t));
    for (int i = 41; i <= 255; i++) {
    data[i-41] = raw[i];
    }
    return data;
}

void ufs_set_data(int disk, uint32_t sector, uint16_t* data) {
    uint16_t* buf = ata_read_sector(disk, sector);
    for (int i = 41; i <= 255; i++) {
    buf[i] = data[i-41];
    }
    ata_write_sector(disk, sector, buf);
}


const char* ufs_get_filename(int disk, uint32_t sector) {
    uint16_t* raw = ata_read_sector(disk, sector);
    char* filename = (char*)malloc(40 * sizeof(char));
    for (int i = 1; i <= 40; i++) {
    filename[i-1] = (char)raw[i];
    }
    return filename;
}

void ufs_set_filename(int disk, uint32_t sector, const char* filename) {
    uint16_t* buf = ata_read_sector(disk, sector);
    for (int i = 1; i <= 40; i++) {
    buf[i] = (uint16_t)filename[i-1];
    }
    ata_write_sector(disk, sector, buf);
}

int ufs_get_last_sector(int disk) {
    uint16_t* sb = ufs_get_super(disk);
    int last = 0;
    for(int i = 2; i <= 255; i++) {
    if(sb[i] == 0) {break;}
    last++;
    }
    return last;
}

int ufs_get_last_fid(int disk) {
    uint16_t* sb = ufs_get_super(disk);
    int last = 0;
    for(int i = 2; i <= 255; i++) {
    if(sb[i] > last) {last = sb[i];}
    }
    return last;
}

int ufs_get_fid(int disk, const char* filename) {
    int last = ufs_get_last_sector(disk);
    for(int i = 1; i <= last; i++) {
    if(strcmp(ufs_get_filename(disk, (uint32_t)last), filename)) { return ufs_sector2fid(disk, i); }
    }
    return -1;
}

int ufs_sector2fid(int disk, uint32_t sector) {
    uint16_t* sb = ufs_get_super(disk);
    return sb[sector + 1];
}


char* ufs_mkfilename(const char* filename) {
    char* ret = (char*)malloc(40 * sizeof(char));
    for(int i = 0; i <= 39 && i <= strlen(filename); i++) {
    ret[i] = filename[i];
    }
    return ret;
}

void ufs_del_file(int disk, const char* filename) {
    int fid = ufs_get_fid(disk, ufs_mkfilename(filename));
    ufs_del_sector(disk, fid);
}

void ufs_write(int disk, const char* filename, const char* data) {
    uint16_t* rawdata = (uint16_t*)malloc(216 * sizeof(uint16_t*));
    for(int i = 0; i <= 215; i++) {
    rawdata[i] = (uint16_t)data[i];
    }
    ufs_write_b(disk, filename, rawdata);
}

const char* ufs_read(int disk, const char* filename) {
    const uint16_t* rawdata = ufs_read_b(disk, filename);
    char* ret = (char*)malloc(216 * sizeof(char));
    for(int i = 0; i <= 215; i++) {
    ret[i] = (char)rawdata[i];
    }
    return ret;
}


void ufs_write_b(int disk, const char* filename, const uint16_t* data) {
    int fid = ufs_get_fid(disk, ufs_mkfilename(filename));
    if(fid == -1) { // File does not exist yet
    fid = ufs_get_last_fid(disk) + 1; // Search for a available FID
    ufs_set_sector(disk, fid); // Create one
    uint32_t sector = ufs_get_sector(disk, fid); // Get its sector
    ufs_set_filename(disk, sector, ufs_mkfilename(filename)); // Set its filename
    ufs_set_data(disk, sector, (uint16_t*)data);
    } else {
    uint32_t sector = ufs_get_sector(disk, fid);
    ufs_set_data(disk, sector, (uint16_t*)data);
    } 
}

const uint16_t* ufs_read_b(int disk, const char* filename) {
    int fid = ufs_get_fid(disk, ufs_mkfilename(filename));
    if(fid == -1) { // File does not exist
    return NULL;
    } else {
    uint32_t sector = ufs_get_sector(disk, fid);
    return ufs_get_data(disk, sector);
    } 
}
