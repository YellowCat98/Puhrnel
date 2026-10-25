ENTRY(kernel_boot)

SECTIONS
{
    . = 1M;

    .text : {
        *(.note*)
        *(.text)
    }

    .data : {
        *(.data)
    }
}