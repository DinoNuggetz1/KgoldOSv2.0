/*ENTRY(_start)
/*SECTIONS {
/*    . = 1M; /* Load kernel at 1MB */
/*    .text : { *(.text) }
/*    .data : { *(.data) }
/*    .bss  : { *(.bss)  }
/*}*/

ENTRY(_start)


ENTRY(kernel_main)

SECTIONS {
    . = 0;
    .text : {
        KEEP(*(.text.entry))
        *(.text .text.*)
    }

    .rodata : { *(.rodata .rodata.*) }
    .data   : { *(.data .data.*) }
    .bss    : { *(COMMON) *(.bss .bss.*) }
}