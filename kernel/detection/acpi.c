#include "acpi.h"

// three of the most significant bits are unused

uint8_t acpi_flags = 0b00000000;

struct data_rsdp* first_digit_of_rsdp;
struct data_rsdt* first_digit_of_rsdt;
struct data_xsdt* first_digit_of_xsdt;
struct data_madt* first_digit_of_madt;
struct data_racp* first_digit_of_facp;


void find_acpi(){
    
    
    for (int c = 0;c<6;++c){
		uint32_t first_digit = 100000;
        uint8_t r = search_table(c, &first_digit);

        acpi_flags |= (r<<c);
        
        if (r==1) {
            configuration_of_tables(c, first_digit);
        }
    }

}


uint8_t search_table(uint8_t i, uint32_t* first_digit){
    
    char first_c;
    char* rest;
    int length;
    
    if(i == RSD_PTR){
        first_c = 'R';
        rest = "SD PTR";
        length = 6;
    }
    
    else if(i == RSDT){
        first_c = 'R';
        rest = "SDT";
        length = 3;
    }
    
    else if(i == XSDT){
        first_c = 'X';
        rest = "SDT";
        length = 3;        
    }
    
    else if(i == MADT){
        first_c = 'A';
        rest = "PIC";
        length = 3;
    }

    else if(i == FACP){
        first_c = 'F';
        rest = "ACP";
        length = 3;
    }

    else if(i == MADT2){
        first_c = 'M';
        rest = "ADT";
        length = 3;
    }

    
    else{
        return 0;
    }

    char* count = (char *)0xE0000;
    const char* end = (char *)0xFFFFF;
    
    while(count<end){
        
        if(*count == first_c){
            uint8_t boolean = 1;
			char* counti = (char*)count;
			++counti;

            for(int c=0; c<length; ++c){
                    if(rest[c] == *counti){
                         ++counti;
                    }    
				    else{
						boolean = 0;
                        break;
                    }
            }
               
            if (boolean == 1){
				    
                    *first_digit = count;
                    
                    return 1;
            }  
        }
	        
        ++count;
            
    }
    return 0;
}


void configuration_of_tables(uint8_t i, uint32_t first_digit){
    
    if(first_digit>0xFFFFF){
        return;
    }
    
    if(i == RSD_PTR){
        uint8_t checksum = 0;
        uint8_t* point_to_first_digit = first_digit;
        
        for(int c = 0; c<20; ++c){
            checksum += *point_to_first_digit;
            ++point_to_first_digit;
            
        }
        
        if (checksum == 0){
            first_digit_of_rsdp = (struct data_rsdp*) first_digit;

        }
        
    }
    
    else if(i == RSDT){

         first_digit_of_rsdt = (struct data_rsdt*) first_digit;

    }
    
    else if(i == XSDT){
        first_digit_of_xsdt = (struct data_xsdt*) first_digit;
    }
    
    else if(i == MADT){
        first_digit_of_madt = (struct data_madt*)  first_digit;
    }

    else if(i == FACP){
        first_digit_of_facp = (struct data_racp*) first_digit;
    }
    
}
