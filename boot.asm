org 0x7c00
bits 16

cli             

lgdt [gdt_descriptor]

mov eax, cr0
or eax, 0x1
mov cr0 , eax

jmp CODE_SEG:init_pm

bits 32

init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    mov ebx, TITLE
    call print

    jmp $

print:
    pusha
    mov edx, 0xb8000

print_loop:
    mov al, [ebx]
    mov ah, 0x0F

    cmp al, 0
    je print_done

    mov [edx], ax
    add ebx, 1
    add edx, 2

    jmp print_loop

print_done:
    popa
    ret



TITLE db "ApolOs", 0

gdt_start:

gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10011010b
    db 11001111b
    db 0x0

gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xaa55