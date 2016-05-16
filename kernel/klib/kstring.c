/*!
 * \file
 * \brief String functions
 *
 * This file constains standard string functions in kernelspace
 */

#include "kstring.h"
#include "stddef.h"

void* memcpy(void* str1_ptr, void* str2_ptr, size_t n) {

    unsigned char* str1 = (unsigned char*) str1_ptr;
    unsigned char* str2 = (unsigned char*) str2_ptr;

    for(unsigned int i=0; i < n; i++) {
        str2[n] = str1[n];
    }

    return str2_ptr;
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
    for (int i = 0; string[i] != '\0'; i++) {
	len++;
    }
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
	    if (s1[i] == s2[i]) {
		continue;
	    } else {
		return 0;
	    }
	}

	return 1;

    } else {
	return 0;
    }
}

unsigned char* strlow (const unsigned char* sl){
		int length = strlen(sl);
		
		unsigned char* returnstring = (unsigned char*)malloc(length* sizeof(unsigned char));
		
		unsigned char c;
		for (int i =0; i < length; ++i){
			c = sl[i];
			if ( c>64 && c<91){
				returnstring[i] = c+32;

			}
			else{
			returnstring[i] = c;
			}
		}
		
		return returnstring;
}
	
unsigned char* strhigh (const unsigned char* su){
		int length = strlen(su);
		
		unsigned char* returnstring = (unsigned char*)malloc(length* sizeof(unsigned char));
		
		unsigned char c;
		for (int i =0; i < length; ++i){
			c = su[i];
			if ( c>96 && c<123){
				returnstring[i] = c-32;	
			}
			else{
			returnstring[i] = c;
			}
			
		}
		return returnstring;	
	
}	

void strlowc (unsigned char* sl){
		int length = strlen(sl);
				
		unsigned char c;
		for (int i =0; i < length; ++i){
			c = sl[i];
			if ( c>64 && c<91){
				sl[i] = c+32;	
			}
		}
}
	
void strhighc (unsigned char* su){
		int length = strlen(su);
				
		unsigned char c;
		for (int i =0; i < length; ++i){
			c = su[i];
			if ( c>96 && c<123){
				su[i] = c-32;	
			}
		}
}



