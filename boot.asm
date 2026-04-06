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

    mov ebp 0x90000
    mov esp, ebp
    
    
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0
dw 0xaa55