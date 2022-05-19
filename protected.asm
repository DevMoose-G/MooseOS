[org 0x7c00]

cli ; disabled all BIOS interrupts
lgdt [GDT_Descriptor] ; loads the GDT
; changes last bit of cr0 to 1
mov eax, cr0
or eax, 1
mov cr0, eax ; now in 32 bit mode
jmp CODE_SEG:start_protected_mode

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
 
	; equ is used to set constants
	CODE_SEG equ code_descriptor - GDT_Start
	DATA_SEG equ data_descriptor - GDT_Start

[bits 32]
var_str:
	times 5 db "This shit really works. Damn! "
	db 0
start_protected_mode:
	; we have to print directly to video memory
	; videoMemory = 0xb8000 (first address of vidMem)
	; first byte is character
	; second byte is color
	mov bx, var_str
	mov ecx, 0xb8000
	mov ah, 0xF9 ; sets color of txt
	jmp print_text

print_text:
	mov al, [bx]
	cmp al, 0
	je $
	mov [ecx], ax
	inc bx
	add ecx, 2	
	jmp print_text

times 510-($-$$) db 0
db 0x55, 0xaa

