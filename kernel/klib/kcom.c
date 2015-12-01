/*!
 * \file
 * \brief Serial communication functions
 *
 * This file contains functions used to communicate with the serial interface
 */

#include "kcom.h"
#include "serial.h"

#include "stdint.h"

/*!
 * \brief Send char
 *
 * This function sends a char to COM1
 * @param c The char to be sent
 */
void serial_writec(char c) {
    send((uint8_t)c);
}

/*!
 * \brief Poll char
 *
 * This function polls a char from COM1
 * @return The polled char
 */
char serial_readc() {
    char buf = (char)recv();
    return buf;
}
