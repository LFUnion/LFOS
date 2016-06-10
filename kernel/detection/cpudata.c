#include "cpudata.h"

uint32_t cpu_data[32];

void use_cpu_id(){
    
    for(uint8_t c = 0; c<6; ++c ){
        
        uint32_t data_a, data_b, data_c, data_d;
        
        __asm__ volatile("cpuid"
        : "=a" (data_a), "=b" (data_b), "=c" (data_c), "=d" (data_d)
        : "a" (c), "c" (0));
        
        cpu_data[c*4] = data_a;
        cpu_data[c*4 + 1] = data_b;
        cpu_data[c*4 + 2] = data_c;
        cpu_data[c*4 + 3] = data_d;
        
    }
    
}

uint32_t interpret_cpu_id_data(const uint8_t number_eax, uint8_t register_number){

    return cpu_data[number_eax * 4 + register_number];
    

}
