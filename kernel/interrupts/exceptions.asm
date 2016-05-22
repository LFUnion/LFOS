[extern c_handler]

%macro EXC_NOERRC 1
    [GLOBAL exc%1]
    exc%1:
        cli
        push byte 0
        push byte %1
        jmp exc_handler
%endmacro

%macro EXC_WERRC 1
    [GLOBAL exc%1]
    exc%1:
        cli
        push byte %1
        jmp exc_handler
%endmacro

; Division by zero
EXC_NOERRC 0

; Debug
EXC_NOERRC 1

; NMI
EXC_NOERRC 2

; Breakpoint
EXC_NOERRC 3

; Detected overflow
EXC_NOERRC 4

; Out of bounds
EXC_NOERRC 5

; Invalid opcode
EXC_NOERRC 6

; No coprocessor
EXC_NOERRC 7

; Double fault
EXC_WERRC 8

; Coprocessor segment overrun
EXC_NOERRC 9

; Bad TSS
EXC_WERRC 10

; Segment not found
EXC_WERRC 11

; Stack fault
EXC_WERRC 12

; General protection fault
EXC_WERRC 13

; Page fault
EXC_WERRC 14

; Unknown interrupt
EXC_NOERRC 15

; Coprocessor fault
EXC_NOERRC 16

; Alignment check
EXC_NOERRC 17

; Machine check
EXC_NOERRC 18

; Reserved
EXC_NOERRC 19
EXC_NOERRC 20
EXC_NOERRC 21
EXC_NOERRC 22
EXC_NOERRC 23
EXC_NOERRC 24
EXC_NOERRC 25
EXC_NOERRC 26
EXC_NOERRC 27
EXC_NOERRC 28
EXC_NOERRC 29
EXC_NOERRC 30
EXC_NOERRC 31


exc_handler:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call c_handler

    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popa
    add esp, 8
    sti
    ret
