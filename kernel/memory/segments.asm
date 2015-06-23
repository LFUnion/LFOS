GLOBAL load_gdt_asm
GLOBAL reload_gdt
GLOBAL reload_segments

reload_gdt:
    ;cli
    ;hlt
    jmp 0x8:reload_segments
    
reload_segments:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
    
load_gdt_asm:
    mov eax, [esp + 4]
    lgdt [eax]
    call reload_gdt
    ret