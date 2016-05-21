/*!
 * \file
 * \brief Type casts
 *
 * This file contains kernelspace type casting functions
 */

#include "kcasts.h"
#include "klib.h"

/*!
 * \brief int -> string
 *
 * This function converts an integer to a string
 * @param input The integer to get converted
 * @return The string
 */
const char * itoa(int input) {
    
    if (input==0){
        return "0";
    }
    
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
