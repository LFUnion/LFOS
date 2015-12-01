/*!
 * \file
 * \brief CPU functions
 *
 * This file contains functions which directly the CPU and the execution of the kernel itself
 */

#include "stdint.h"

#include "cpu.h"
#include "portio.h"

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