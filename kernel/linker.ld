ENTRY(_start)

SECTIONS
{
    . = 0x10000;

    .text ALIGN(4096)  :   {
        *(.text)
    }
    .data ALIGN(4096) : {
        *(.data)
    }
    .rodata ALIGN(4096) : {
        *(.rodata)
    }
    .bss ALIGN(4096) : {
        *(.bss)
    }
}
