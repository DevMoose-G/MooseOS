global outb
global inb
global cursor_enable
global video_mode

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

; turns to the video mode, but uses bios interrupt
video_mode:
	mov ah, 0x00 ; function 00h = mode set
	mov al, 0x13 ; 256-color mode 
	int 0x10
	ret
