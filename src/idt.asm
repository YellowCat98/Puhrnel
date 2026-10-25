global syscall_handler
extern syscall_dispatch

syscall_handler:
    pusha
    mov ebp, esp
    and esp, -16
    sub esp, 8
    push ebp
    call syscall_dispatch
    mov esp, ebp
    popa
    iretd