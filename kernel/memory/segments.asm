GLOBAL load_gdt_asm
GLOBAL reload_gdt
GLOBAL reload_segments

load_gdt_asm:
    mov eax, [esp + 4]
    lgdt [eax]
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ;jmp 0x8:flush_gdt
    ret

flush_gdt:
    ret
