#include "apic.h"

#define LAPIC     0
#define IOAPIC    1
#define APICIN    2

uint8_t * lapic_p;
uint8_t * ioapic_p;

struct data_lapic* d_lapic[10];
struct data_ioapic *d_ioapic;
struct data_iapic *d_iapic;

int lapicscpu = 0;

int apictablemadt(){
    
    if((0b0001000 & acpi_flags)==0){
        return 0;
    }

    lapic_p = (uint8_t *) first_digit_of_madt->localapicadr;

    uint8_t *count = (uint8_t *)(first_digit_of_madt + 1);
    uint8_t *end = (uint8_t *)first_digit_of_madt + first_digit_of_madt->length;
    int i =0;
    
    while (count < end){

        uint8_t number = *(uint8_t *)count;
        uint8_t length = *((uint8_t *)count + 1);

        if (number == LAPIC && i<10){
            d_lapic[i] = (struct data_lapic *)count;
            
            ++i;
            ++lapicscpu;
            
        }
        
        else if (number == IOAPIC){

            d_ioapic = (struct data_ioapic *)count;

            ioapic_p = (uint8_t *)d_ioapic->ioapicaddress;
        }
        
        else if (number == APICIN){
			
            d_iapic = (struct data_iapic *)count;

        }

        count += length;
    }
    return 1;
}



uint64_t get_lapic_adress(){
    
    uint64_t i = crdmsr(0x1B);
    if(i!=0){
        return i;
    }
}

void apic_init(){
    
    uint32_t data;
    asm volatile
    ("cpuid" 
     : "=b" (data)
     : "a" (0x01), "c" (0));
    
    data = data>>24;
    
    if (apictablemadt()==0 || data==0){
        return;
    }
    
    picdis();
        
    localapic_config();
    ioapic_config();
    
    asm volatile
    ("sti"); 

        
}

void localapic_config(){
     volatile uint32_t* l = (uint32_t*)( (uint8_t*)crdmsr(0x1B) + 0x80);
     *l = 0;
     
     l = (uint32_t*)((uint8_t*)crdmsr(0x1B) + 0xE0);
     *l = 0xFFFFFFFF;
     
     l = (uint32_t*)((uint8_t*)crdmsr(0x1B) + 0xD0);
     *l = 0x01000000;

     l = (uint32_t*)((uint8_t*)crdmsr(0x1B) + 0xF0);
     *l = 0x1FF;


}

void ioapic_config(){
     
     uint32_t numberapicp =  (readapicreg(1) >> 16) & 0xff;
     ++numberapicp;
     
     for(uint32_t c = 0; c<numberapicp; ++c){
         writeapicreghex(0x10 + 2*c, 1 << 16);
         writeapicreghex(0x11 + 2*c, 0);
     }
     
}

void writeapicreghex (uint8_t registern, uint32_t hex){
    volatile uint32_t* lr = (uint32_t*) (ioapic_p);
    volatile uint32_t* lh = (uint32_t*) (ioapic_p +0x10);

    *lr = registern;
    *lh = hex;
}

uint32_t readapicreg (uint8_t registern){

    volatile uint32_t* lr = (uint32_t*) (ioapic_p);
    volatile uint32_t* lh = (uint32_t*) (ioapic_p +0x10);

    *lr = registern;
    return *lh;
}

void pic_dis() {
    outb(0x20, 0x11);
    outb(0xa0, 0x11);

    outb(0x21, 0xe0);
    outb(0xa1, 0xe8);

    outb(0x21, 0xff);
    outb(0xa1, 0xff);
}
