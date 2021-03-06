/*!
 * \file
 * \brief String functions
 *
 * This file constains standard string functions in kernelspace
 */

#include "kstring.h"
#include "stddef.h"

void* memcpy(void* ptr1, void* ptr2, size_t n) {
    for(unsigned int i = 0; i < n; i++) {
        *(int*)ptr2 = *(int*)ptr1;
        ptr1++;
        ptr2++;
    }

    return ptr2;
}

void* memset(void* ptr, int value, size_t n) {
    for (size_t i = 0; i < n; i++) {
        int* cur_addr = ptr + i;
        *cur_addr = value;
    }

    return ptr;
}

/*!
 * \brief Lenght of a string
 *
 * This function returns the lenght of a string
 *
 * @param string The string
 * @return The lenght of the string
 */
int strlen(const char* string) {
    int len = 0;

    for (int i = 0; string[i] != '\0'; i++)
        len++;

    return len;
}

/*!
 * \brief Compares strings
 *
 * This function compares two strings and checks whether they are equal or not
 *
 * @param s1 First string
 * @param s2 Second string
 * @return 0 if not equal, 1 if equal
 */
int strcmp (const char* s1, const char* s2) {
    if (strlen(s1) == strlen(s2)) {
        for (int i = 0; i < strlen(s1); i++) {
            if (s1[i] == s2[i])
                continue;
            else
                return 0;
        }

        return 1;
    } else
        return 0;
}

char* strcpy (char* dest, char* src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = src[i];

    return dest;
}

char* strcat(char* dst, char* src) {
    const int len = strlen(dst);
    int i = len;

    do {
        dst[i] = src[i-len];
        i++;
    } while (src[i-len] != '\0');

    dst[i] = '\0';
    return dst;
}

char* strlow (const char* sl) {
    int length = strlen(sl);
    char* returnstring = (char*)malloc(length* sizeof(char));
    char c;

    for (int i =0; i < length; ++i) {
        c = sl[i];

        if ( c>64 && c<91)
            returnstring[i] = c+32;
        else
            returnstring[i] = c;
    }

    return returnstring;
}

char* strhigh (const char* su) {
    int length = strlen(su);
    char* returnstring = (char*)malloc(length* sizeof(char));
    char c;

    for (int i =0; i < length; ++i) {
        c = su[i];

        if ( c>96 && c<123)
            returnstring[i] = c-32;
        else
            returnstring[i] = c;
    }

    return returnstring;
}

void strlowc (char* sl) {
    int length = strlen(sl);
    char c;

    for (int i =0; i < length; ++i) {
        c = sl[i];

        if ( c>64 && c<91)
            sl[i] = c+32;
    }
}

void strhighc (char* su) {
    int length = strlen(su);
    char c;

    for (int i =0; i < length; ++i) {
        c = su[i];

        if ( c>96 && c<123)
            su[i] = c-32;
    }
}



