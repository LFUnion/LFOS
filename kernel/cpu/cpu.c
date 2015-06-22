#include "stdint.h"

#include "cpu.h"
#include "portio.h"

void cpu_reset()
{
    cpu_cli();
    outb(0x64, 0xFE);
    hlt_loop:
    cpu_halt();
    goto hlt_loop;
}

void cpu_halt()
{
    asm volatile("hlt");
}

void cpu_cli()
{
    asm volatile("cli");
}