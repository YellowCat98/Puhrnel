global big_boobs

big_boobs:
    mov eax, 1
    mov ebx, 2
    int 0x80
    mov esi, eax

    mov eax, 0
    mov ebx, 0
    mov ecx, esi
    mov edx, 7
    int 0x80
    ret