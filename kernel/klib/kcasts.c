/*!
 * \file
 * \brief Type casts
 *
 * This file contains kernelspace type casting functions
 */

#include "kcasts.h"
#include "klib.h"

#define OFFSETNUMBERS 48

/*
 * casts a double or float in a string (character) list
 *
 */

char * stringFromDouble(const double input, int8_t after) {
    if(input == 0)
        return "0.0";

    if(after>15)
        after = 15;
    else if(after<1)
        after = 1;

    char * rstr = malloc((sizeof(char))*(100 + after));
    uint8_t write = 0;
    const double input_abs = abs(input);
    int64_t i = (int64_t) input_abs;
    double tail = input_abs - (double) i;

    if(input_abs != input) {
        rstr[write] = '-';
        ++write;
    }

    if(i == 0) {
        rstr[write] = OFFSETNUMBERS;
        ++write;
    }

    while (i!=0) {
        rstr[write] = OFFSETNUMBERS + (i%10);
        i /= 10;
        ++write;
    }

    rstr[write] = '.';
    ++write;
    const uint8_t afterwrite = write + after;

    for (write; write<afterwrite; ++write) {
        tail *= 10;
        i = tail;
        tail = tail - i;
        rstr[write] = OFFSETNUMBERS + i;
    }

    tail *= 10;
    i = tail;

    if(i>4) {
        uint8_t write2 = write -1;

        if(rstr[write2] != (OFFSETNUMBERS +9))
            rstr[write2] = rstr[write2] +1;
        else {
            while(rstr[write2] == (OFFSETNUMBERS +9) || rstr[write2] == '.') {
                if (rstr[write2] == '.') {
                    --write2;
                    continue;
                }

                rstr[write2] = OFFSETNUMBERS;
                --write2;
            }

            rstr[write2] = rstr[write2] +1;
        }
    }

    rstr[write] = '\0';
    return rstr;
}

unsigned int uintFromString(char* restrict input) {
    unsigned int rnumber = 0 ;
    int stringlength = strlen(input)-1;
    int factor = 1 , test;

    for(stringlength; stringlength>-1; --stringlength) {
        test = input[stringlength]-OFFSETNUMBERS;

        if(!(test>-1 && test<10))
            return 0;

        rnumber += (test)*factor;
        factor *= 10;
    }

    return rnumber;
}

int intFromString(char* restrict input) {
    int rnumber = 0;
    int stringlength = strlen(input)-1;
    int factor = 1, test;

    for(stringlength; stringlength>-1; --stringlength) {
        test = input[stringlength]-OFFSETNUMBERS;

        if(!(test>-1 && test<10)) {
            if((test == '-'-OFFSETNUMBERS) && stringlength == 0) {
                rnumber = -rnumber;
                break;
            } else
                return 0;
        }

        rnumber += (test)*factor;
        factor *= 10;
    }

    return rnumber;
}

/*!
 * \brief int -> string
 *
 * This function converts an integer to a string
 * @param input The integer to get converted
 * @return The string
 */
const char * itoa(int input) {
    if (input==0)
        return "0";

    int input_bak = input;
    int input_l = 0;

    while(input) {
        input_l++;
        input /= 10;
    }

    input = input_bak;
    char tmp[input_l];
    int i = 0;

    while(input) {
        tmp[i] = charFromDigit(input % 10);
        i++;
        input /= 10;
    }

    // Simple array reversing
    i = 0;
    char* ret;
    ret = (char*)malloc(input_l * sizeof(char) +1);

    for (int l = input_l-1; l > -1; l--) {
        ret[i] = tmp[l];
        i++;
    }

    ret[i] = '\0';
    return ret;
}

const char * stringFromInt(int input) {
    return itoa(input);
}

int atoi(char* string) {
    int ret = 0;
    int str_len = strlen(string)-1;

    for (int i = str_len; i >= 0; i--)
        ret += (string[i] - 48) * pow(10, str_len-i);

    return ret;
}

/*!
 * \brief int -> char
 *
 * This function converts a digit to a single char
 * @param digit The digit to get converted
 * @return The char
 */
char charFromDigit(int digit) {
    if (digit >= 0 && digit <= 9)
        return 48 + digit;
    else
        return '0';
}
