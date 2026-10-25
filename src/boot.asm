bits 32 ; so sad

section .multiboot
align 8
multiboot_header:
    dd 0xe85250d6
    dd 0
    dd header_end - multiboot_header
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - multiboot_header))

    dw 0
    dw 0
    dw 8
header_end:

extern kmain
extern idt_init

section .text
global kernel_boot

kernel_boot:
    mov esp, stack_top
    cld

    call idt_init
    call kmain

section .bss
align 16
stack_bottom:
    resb 16384
stack_top: