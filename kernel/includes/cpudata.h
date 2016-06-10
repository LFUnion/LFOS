#ifndef CPUDATA_H
#define CPUDATA_H

#include <stdint.h>

enum eax0a {maxinput = 0};

enum eax0b {name1 = 0};

enum eax0c {name2 = 0};

enum eax0d {name3 = 0};

/*
 * missimg
 *  
 */


enum eax1b {brandindex = 0, cachelinesize = (1<<8), numberoflogical = (1<<16), localapicid_pro = (1<<24) };

/*
 * missimg
 *  
 */

/*
enum eax2a {};

enum eax3a {};

enum eax4a {};

enum eax5a {};
*/



void use_cpu_id();
uint32_t interpret_cpu_id_data(const uint8_t number_eax, uint8_t register_number);


#endif 
