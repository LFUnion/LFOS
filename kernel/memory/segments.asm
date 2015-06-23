[BITS 32]

GLOBAL load_gdt_asm
GLOBAL reload_selector

SECTION .text

gdtr DW 0
     DD 0

load_gdt_asm:
    xor eax, eax
    mov ax, ds
    shl eax, 4
    add eax, 'GDT'
    mov [gdtr + 2], eax
    mov eax, 'GDT_end'
    sub eax, 'GDT'
    mov [gdtr], ax
    lgdt [gdtr]
    jmp 0x08:reload_selector
 
reload_selector:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret