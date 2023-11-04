ENTRY(_start)

SECTIONS
{
    . = 1M;

    .multiboot :
    {
        *(.multiboot)
    }
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.text)
        *(.eh_frame)
        *(.ctors)
    }

    .rodata BLOCK(4K) : ALIGN(4k)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
