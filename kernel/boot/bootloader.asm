; This is the simple bootloader of LFOS.

MBALIGN  equ 1<<0
MEMINFO  equ 1<<1
FLAGS    equ MBALIGN | MEMINFO
MAGIC    equ 0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .text

; Multiboot header
dd MAGIC
dd FLAGS
dd CHECKSUM

; Start "function"
global _start
_start:
    mov esp, stack_end ; Stack setup
    extern kmain ; Defined in kernel/kernel.c
    call kmain
    cli
    
.hang:
    hlt
    jmp .hang
    


section .bss

stack_begin:
    resb 4096 ; 4kB stack
stack_end:
