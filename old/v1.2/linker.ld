/*ENTRY(_start)
/*SECTIONS {
/*    . = 1M; /* Load kernel at 1MB */
/*    .text : { *(.text) }
/*    .data : { *(.data) }
/*    .bss  : { *(.bss)  }
/*}*/

ENTRY(_start)

SECTIONS {

    . = 1M;

    .text BLOCK(4K) : ALIGN(4K)
    {

        *(.multiboot)
        *(.text)
    }


    .rodata BLOCK(4K) : ALIGN(4K)
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

