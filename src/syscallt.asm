global big_boobs

big_boobs:
    mov eax, 0
    mov ebx, 0
    mov ecx, message
    mov edx, 4
    int 0x80
    ret

message:
    db "hello from assembly, BOOYAH! 🤣🤣🤣🤣", 10, 0