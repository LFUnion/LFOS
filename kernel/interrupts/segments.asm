GLOBAL reload_segments

SECTION .text

reload_segments:
    jmp 0x08:.reload_selector
    
.reload_selector:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret