/*!
 * \file
 * \brief Filesystem functions
 *
 * This file contains kernelspace filesystem functions. They are currently using uFS
 */

#include "kfs.h"

/*!
 * \brief Write data to disk
 *
 * This function writes data using the uFS, see the uFS documentation
 *
 * @param filename The filename the data should get associated with
 * @param data A string
 */
void write(const char* filename, const char* data) {
    ufs_write(0, filename, data);
}

/*!
 * \brief Read data from disk
 *
 * This function reads data using the uFS, see the uFS documentation
 *
 * @param filename The filename of the file
 * @return The read data
 */
const char* read(const char* filename) {
    return ufs_read(0, filename);
}

/*!
 * \brief Write sectors to disk
 *
 * This function writes sectors using the uFS, see the uFS documentation
 *
 * @param filename The filename the data should get associated with
 * @param data A sector of data
 */
void writeb(const char* filename, const uint16_t* data) {
    ufs_write_b(0, filename, data);
}

/*!
 * \brief Read sectors from disk
 *
 * This function reads sectors using the uFS, see the uFS documentation
 *
 * @param filename The filename of the file
 * @return The read sector
 */
const uint16_t* readb(const char* filename) {
    return ufs_read_b(0, filename);
}
