#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define VGA_WIDTH 80
#define VIDEO_START 0xb8000

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_YELLOW = 14,
	VGA_COLOR_LIGHT_WHITE = 15
};

extern void outb(int port, int data);
extern int inb(int port);
extern void video_mode();

void update_cursor(int x, int y){
	int pos = y * VGA_WIDTH + x;
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, (int) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (int) ((pos >> 8) & 0xFF));
}

void plotPixel(int x, int y){
	typedef unsigned char byte;
	byte* VGA = (byte*)0xA0000000L;
	unsigned short offset = 320*y + x;
	VGA[offset] = 0x09;
}

int printAt(const char* str, int vidAddress){
	while(*str != '\0'){
		*(char*)vidAddress = *str;
		vidAddress+=2;
		str++;
	}
	
	// updates cursor
	update_cursor((vidAddress - VIDEO_START)/2, 0);
	return vidAddress;
}


void cursor_enable(int cursor_start, int cursor_end){
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end); 
}


extern void main(){
	int vidAddress = VIDEO_START;
	cursor_enable(0, 25);
	vidAddress = printAt("Damn this works! ", vidAddress);	
	vidAddress = printAt("I can write multiple lines from C to here. ", vidAddress);
	vidAddress = printAt("With this one sentence, I can write enough to fill a whole line if I can just waffle for long enough to fill any screen size.", vidAddress);
	//plotPixel(8, 8);
}
