; boot.asm — fixed version
; nasm -f bin boot.asm -o boot.bin

BITS 16
ORG 0x7C00

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; Set ES = 0x1000 (must use AX → ES)
    mov ax, 0x1000
    mov es, ax
    xor bx, bx

    ; Read 1 sector from LBA 1 into ES:BX = 0x1000:0000
    mov ah, 0x02        ; BIOS read
    mov al, 0x01        ; sectors
    mov ch, 0x00        ; cylinder
    mov dh, 0x00        ; head
    mov cl, 0x02        ; sector (starts at 1)
    int 0x13

    jc disk_error       ; if carry flag set → error

    ; Switch to protected mode
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp 0x08:protected_mode

disk_error:
    mov si, err_msg
.print_err:
    lodsb
    or al, al
    jz $
    mov ah, 0x0E
    int 0x10
    jmp .print_err

err_msg db "Disk read error", 0

[BITS 32]
protected_mode:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov esp, 0x90000

    ; Jump to kernel at 0x100000
    jmp 0x100000

gdt_start:
    dq 0x0000000000000000
    dq 0x00CF9A000000FFFF
    dq 0x00CF92000000FFFF
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 510-($-$$) db 0
dw 0xAA55

