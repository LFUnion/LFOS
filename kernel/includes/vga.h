#ifndef VGA_H
#define VGA_H

#include <stdint.h>

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

void kprintc(uint8_t chr, uint8_t clr, uint8_t x, uint8_t y);
void kprint_raw(const char text[]);
void klog(const char text[]);
void klogi(const char text[]);
void kclear();

#endif /* VGA_H */
