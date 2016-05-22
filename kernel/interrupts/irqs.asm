[extern irq_handler]

%macro IRQ 1
    [GLOBAL irq%1]
    irq%1:
        pusha
        
        push byte %1
        call irq_handler
        add esp, 4
                
        popa
        
        sti
        iret
%endmacro

IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15
