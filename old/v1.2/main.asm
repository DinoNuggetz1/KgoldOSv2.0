[bits 32]

MBOOT_PAGE_ALIGN    equ 1 << 0
MBOOT_MEM_INFO      equ 1 << 1
MBOOT_GRAPHICS      equ 1 << 2
MBOOT_HEADER_MAGIC  equ 0x1BADB002
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_GRAPHICS
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

section .multiboot
align 4
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM
    
    dd 0, 0, 0, 0, 0 

    dd 0    ; Mode type (0 = linear)
    dd 1024 ; Width
    dd 768  ; Height
    dd 32   ; Depth

section .text
global _start
extern kernel_main

_start:
    push ebx 
    call kernel_main
.hang:
    hlt
    jmp .hang
