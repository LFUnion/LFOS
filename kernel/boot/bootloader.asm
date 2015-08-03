; This is the simple bootloader of LFOS.

MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
FLAGS    equ MBALIGN | MEMINFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .text
global _start
_start:
    extern kmain
    call kmain
    cli
    
.hang:
    hlt
    jmp .hang
    