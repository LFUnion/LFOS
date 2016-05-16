#ifndef DRIVER_API_H
#define DRIVER_API_H

#include <stdint.h>
#include "klib.h"

#define ATA 0
#define KEYBOARD 1
#define RTC 2
#define SERIAL 3
#define VGA 4

// Variables

/*
enum drivertypes = 
{
    ATA,
    KEYBOARD,
    RTC, 
    SERIAL, 
    VGA
};
*/

union function_data{
    // uint8_t functions
    uint8_t (*func_8)          ();
    uint8_t (*func_8_8)        (uint8_t);
    uint8_t (*func_8_8_8)      (uint8_t, uint8_t);
    uint8_t (*func_8_i)        (int);

    // unint16_t functions
    uint16_t* (*func_16_i_32)  (int, uint32_t);
    uint16_t* (*func_16_i_32_i) (int, uint32_t, int);

    //functions without a return value
    void (*func_v)             ();
    void (*func_v_8)           (uint8_t);
    void (*func_v_8_8)         (uint8_t, uint8_t);
    void (*func_v_i)           (int);
    void (*func_v_8_i)         (uint8_t, int);
    void (*func_v_i_32_16p)    (int , uint32_t , uint16_t* );
    void (*func_v_i_32_i_16p)  (int , uint32_t , int , uint16_t* );
    void (*func_v_8_8_8_8)     (uint8_t , uint8_t , uint8_t , uint8_t );
    void (*func_v_cp)          (const char*);

    // int functions
    int  (*func_i)             ();
    int  (*func_i_i)           (int);

};


struct driver_data {
    uint8_t driver_number;
    uint8_t number_of_functions;
    uint8_t driver_priority;
    char* driver_description;
};

// Functions

void driver_counter_reset();
void driver_counter_increase();
void send_to_master_api(int number);

// Driver functions
void ata_send();
void keyboard_send();
void serial_send();
void vga_send();

void ata_use(const int func);
void keyboard_use(const int func);
void serial_use(const int func);
void vga_use(const int func);


#endif 
