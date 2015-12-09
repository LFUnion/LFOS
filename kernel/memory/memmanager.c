/*!
 * \file
 * \brief Dynamic memory management
 *
 * This file contains the dynamic memory management
 */

#include "memmanager.h"

// This is just a very simple MM to start with

/*!
 * \brief Adress pointer
 *
 * This is a pointer to the highest unused address
 */
void* crnt_addr = (void*)0x040000; // 4MB

/*!
 * \brief Allocates memory
 *
 * This function allocates a block of memory of size n
 *
 * @param n Size of the memory to allocate
 * @return Pointer to the allocated block
 */

void* malloc (size_t n) {
    void* return_addr = crnt_addr;
    crnt_addr += n;
    return return_addr;
}

/*
void func_scalloc(short value, short* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}
void func_icalloc(int value, int* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}
void func_lcalloc(long value, long* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}
void func_llcalloc(long long value, long long* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}
void func_fcalloc(float value, float* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}
void func_dcalloc(double value, double* count_ptr, unsigned long max){
    unsigned long count =0;
    while (count<max){
        *count_ptr = value;
        ++count_ptr;
        ++count;
    }
}

void* ncalloc (unsigned long n, unsigned int size , double value) {
    
    static void* error_addr = ((void*)0x03FFFC);
    //*error_addr = -1;
    
    if (!(size==sizeof(short) || size==sizeof(int) || size==sizeof(long) || size==sizeof(long long) || size==sizeof(double) || size==sizeof(float))){
        return  error_addr; // (void*) error_addr
    }
    char dfvar;
    if (value != ((long)value)){
        dfvar = 'f'; 
    }
    else {
        dfvar = 'i'; 
    }
    
    void* return_addr = crnt_addr;
    void* count_addr = crnt_addr;
    
    if (size==sizeof(short) && dfvar=='i'){
         func_scalloc(value,(short*)count_addr, n);
    }
    else if (size==sizeof(int) && dfvar=='i'){
         func_icalloc(value,(int*)count_addr, n);         
    }
    else if (size==sizeof(long) && dfvar=='i'){
         func_lcalloc(value,(long*)count_addr, n);         
    }
    else if (size==sizeof(long long) && dfvar=='i'){
         func_llcalloc(value,(long long*)count_addr, n);         
    }
    else if (size==sizeof(float) && dfvar=='f'){
         func_fcalloc(value,(float*)count_addr, n);         
    }
    else if (size==sizeof(double) && dfvar=='f'){
         func_dcalloc(value,(double*)count_addr, n);         
    }
    else{
        return  error_addr; // (void*) error_addr
    }
    crnt_addr += (n*size);
    
    return return_addr;
}

void* calloc(unsigned long n, unsigned int size){
    return ncalloc (n, size , 0);
}
*/
