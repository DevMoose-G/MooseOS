global cursor_enable
;type cursor_enable,%function
cursor_enable:
	; r0 is cursor start
	; r1 is cursor end
	; stores the flags and registers on the stack
	;pushf

	mov bh, [esp+4] ; takes the first int
	mov bl, [esp+8] ; takes the second int
	
	; outb(0x3D4, 0x0A)
	mov dx, 0x3D4
	mov al, 0x0A
	out dx, al

	; outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start)
	mov dx, 0x3D5
	in al, dx
	;mov al, [es*16+di]
	and al, 0xC0
	or al, bh
	out dx, al

	; outb(0x3D4, 0x0B)
	mov dx, 0x3D4
	mov al, 0x0B
	out dx, al

	; outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end)
	mov dx, 0x3D5
	in al, dx
	;mov al, [es*16+di]
	and al, 0xE0
	or al, bl
	out dx, al 

	ret

