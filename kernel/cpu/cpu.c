/*!
 * \file
 * \brief CPU functions
 *
 * This file contains functions which directly the CPU and the execution of the kernel itself
 */

#include "stdint.h"
#include "cpuid.h"

#include "cpu.h"
#include "portio.h"
#include "klib.h"

/*!
 * \brief CPU reset
 *
 * This function will immediately disable all interrupts and reset the CPU
 */
void cpu_reset()
{
    cpu_cli(); // Clear all interrupts
    outb(0x64, 0xFE); // Set the reset line
    hlt_loop: // hlt_loop start label
    cpu_halt(); // Halt the CPU (This will trigger the reset)
    goto hlt_loop; // If it failed, try again
}

/*!
 * \brief CPU halt
 *
 * This function will immediately halt the CPU
 */
void cpu_halt()
{
    asm volatile("hlt");
}

/*!
 * \brief Disable IRQ
 *
 * This function will immediately disable all IRQs
 */
void cpu_cli()
{
    asm volatile("cli");
}

/*!
 * \brief Disable IRQ
 *
 * This function will immediately restore all IRQs
 */
void cpu_sti()
{
    asm volatile("sti");
}

char* cpu_getVendor() {
    char* vendor = (char*)malloc(3 * 4 * sizeof(char) + 1);
    unsigned int* eax = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned int* ebx = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned int* ecx = (unsigned int*)malloc(sizeof(unsigned int));
    unsigned int* edx = (unsigned int*)malloc(sizeof(unsigned int));

    int success = __get_cpuid(0, eax, ebx, ecx, edx);
    if (success) {

        // CPUID successful
        for (int index = 0; index < 12; index++) {
            if (index < 4) {
                // EBX
                vendor[index] = (char)(*ebx >> (index*8));
                //print_raw("1");
            } else if (index < 8) {
                // ECXmake

                vendor[index] = (char)(*edx >> ((index-4)*8));
                //print_raw("2");
            } else if (index < 12) {
                // EDX
                vendor[index] = (char)(*ecx >> ((index-8)*8));
                //print_raw("3");
            }
        }
        
        // Null-Terminator
        vendor[12] = 0;

    } else {
        // CPUID fails
        vendor = "-GenericX86-";
    }
    
    free(eax);
    free(ebx);
    free(ecx);
    free(edx);
    
    return vendor;
}

uint8_t get_number_of_cores(){
    uint32_t data;
    asm volatile
    ("cpuid" 
     : "=a" (data)
     : "a" (0x04), "c" (0));
    
    uint8_t cores = ((data>>26) & 0xFF);
    ++cores;
	
    return cores;
}
