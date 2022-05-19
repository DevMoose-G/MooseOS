[org 0x7c00]
; 1st Loads Kernel from Disk
KERNEL_LOCATION equ 0x1000

BOOT_DISK: db 0
mov [BOOT_DISK], dl

mov ax, 0
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 20 ; 20 is 10 KB check if it is enough

mov ah, 0x02
mov al, dh
mov ch, 0x00
mov dh, 0x00
mov cl, 0x02
mov dl, [BOOT_DISK]
int 0x13 ; no error management yet

; 2nd Switches to TextMode which clears the screen
mov ah, 0x0
mov al, 0x3
int 0x10 ; text mode

; 3rd Switches to Protected Mode

mov al, 0
adc al, 0
cmp al, 1
je errorStr

mov ah, 0x0e
mov al, [0x7e00]

printStr:
	int 0x10
	inc bx
	mov al, [bx]
	cmp al, 0
	jne printStr

jmp $

errorStr:
	mov ah, 0x0e
	add al, 48
	mov al, 'E'
	int 0x10

times 510-($-$$) db 0
db 0x55, 0xaa

