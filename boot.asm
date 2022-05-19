[org 0x7c00]
; 1st Loads Kernel from Disk
KERNEL_LOCATION equ 0x1000

BOOT_DISK: db 0
mov [BOOT_DISK], dl

mov ax, ax
mov es, ax
mov ds, ax
mov bp, 0x8000
mov sp, bp

mov bx, KERNEL_LOCATION
mov dh, 2 ; 20 is 10 KB check if it is enough

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
; equ is used to set constants
CODE_SEG equ code_descriptor - GDT_Start
DATA_SEG equ data_descriptor - GDT_Start

cli ; disabled all BIOS interrupts
lgdt [GDT_Descriptor] ; loads the GDT
; changes last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax ; now in 32 bit mode
jmp CODE_SEG:start_protected_mode

jmp $
; db is one byte, dw is two bytes, dd is four bytes
GDT_Start:
	null_descriptor:
		dd 0 ; four times 00000000
		dd 0 ; four times 00000000
	code_descriptor:
		; first 16 bits of limit
		dw 0xffff
		; first 24 bits of base
		dw 0
		db 0
		; present, privelege, and type flags 
		db 0b10011010
		; Other flags and last four bits of limit
		db 0b11001111
		; Last 8 bits of base
		db 0
	data_descriptor:
		; first 16 bits of limit
		dw 0xffff
		; first 24 bits of base
		dw 0
		db 0
		; present, privelege, and type flags 
		db 0b10010010
		; Other flags and last four bits of limit
		db 0b11001111
		; Last 8 bits of base
		db 0
	GDT_End:
	GDT_Descriptor:
		dw GDT_End - GDT_Start - 1 ; size
		dd GDT_Start ; start
 

[bits 32]
start_protected_mode:
	; setup segment registers and stack
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp
	
	jmp KERNEL_LOCATION ; go to kernel

times 510-($-$$) db 0
db 0x55, 0xaa

