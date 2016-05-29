/*
LFOS, a simple operating system.
Copyright (C) 2016 LFUnion.

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


#ifndef KMATH_H
#define KMATH_H

#include <stdint.h>

// Defines 
#define PI 3.14159265
#define E 2.71828183

// Functions

// normal

double abs(const double value);
double pow( const double base, const double exponent);
double root (const double radicand, double exponent);


// experimental and normal

double secondroot (const double radicand);
double pow_exp (const double base, const double exponent);


// extern and inline

extern inline uint64_t round (const double value);
extern inline uint64_t factorial(const int32_t value);
extern inline double pow_i(const double base, const int64_t exponent);


// static

static inline uint64_t abs_i(int64_t value);
static double continuous_fraction_root(double minus, const double radicant, uint8_t max);


#endif 
