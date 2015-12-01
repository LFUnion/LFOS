/*!
 * \file
 * \brief Inbound ports
 *
 * This file contains functions to handle communication with the inbound CPU ports
 */

#include "stdint.h"
#include "inb.h"

/*
LFOS, a simple operating system.
Copyright (C) 2015 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
 * \brief Receive word
 *
 * @param port (16 bit) Adress of the port
 * @return (8 bit) The data received
 */
uint8_t inb(uint16_t port)
{
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a" (value) : "Nd" (port));
    return value;
}
