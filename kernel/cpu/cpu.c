#include "stdint.h"

#include "cpu.h"
#include "portio.h"

void cpu_reset()
{
    cpu_cli(); // Clear all interrupts
    outb(0x64, 0xFE); // Set the reset line
    hlt_loop: // hlt_loop start label
    cpu_halt(); // Halt the CPU (This will trigger the reset)
    goto hlt_loop; // If it failed, try again
}

void cpu_halt()
{
    asm volatile("hlt");
}

void cpu_cli()
{
    asm volatile("cli");
}