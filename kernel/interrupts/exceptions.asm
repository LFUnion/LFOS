GLOBAL exc0

extern c_handler

; Division by zero error
exc0:
    cli
    push byte 0
    push byte 0
    jmp exc_handler

exc_handler:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, c_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret