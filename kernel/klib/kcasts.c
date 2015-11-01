#include "kcasts.h"

int hexToInt(uint8_t input) {
    int retval = input;
    return retval;
}

const char** stringFromInt(int input) {

    int input_bak = input;
    static int input_l = 0;
    while(input){
           input_l++;
       input /= 10;
    }

    input = input_bak;
    char tmp[input_l];
    static int i;
    while(input){
        tmp[i] = charFromDigit(input % 10);
	i++;
       	input /= 10;
    }
    
    // Simple array reversing
    i = 0;
    char ret[input_l];
    for (int l = input_l-1; l > -1; l--) {
	ret[i] = tmp[l];

	i++;
    }
    
    return ret;
}

char charFromDigit(int digit) {
    if (digit == 0) {
	return '0';
    } else if (digit == 1) {
	return '1';
    } else if (digit == 2) {
	return '2';
    } else if (digit == 3) {
	return '3';
    } else if (digit == 4) {
	return '4';
    } else if (digit == 5) {
	return '5';
    } else if (digit == 6) {
	return '6';
    } else if (digit == 7) {
	return '7';
    } else if (digit == 8) {
	return '8';
    } else if (digit == 9) {
	return '9';
    } else {
	return '0';
    }
}
