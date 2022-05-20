global outb
global inb
global cursor_enable

; outputs al to the port dx
outb: ; (dx, al)

	; dx is the port
	; al is the data fed to the port
	mov dx, [esp+4]
	mov al, [esp+8]
	out dx, al
	ret

; returns the data at port dx
inb: ; (dx) 
	mov dx, [esp+4]
	in eax, dx ; eax is where you store what you return 
	ret

