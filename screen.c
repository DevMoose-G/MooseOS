#include <system.h>

int cursor_x = 0;
int cursor_y = 0;

void update_cursor(){
	int pos = cursor_y * VGA_WIDTH + cursor_x;
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, (int) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (int) ((pos >> 8) & 0xFF));
}

void clr_screen(){
	for(int i = 0; i < VGA_HEIGHT; i++){
		for(int j = 0; j < VGA_WIDTH; j++){
			int pos = (i*VGA_WIDTH) + j;
			int vidAddress = VIDEO_START + (pos*2);
			*(char*)vidAddress = ' ';
			*(char*)(vidAddress+1) = DEFAULT_COLOR;
		}
	}
	cursor_x = 0;
	cursor_y = 0;
	update_cursor();
}

int terminal_print(const char* str){
	while(*str != '\0'){
		if(*str == '\n'){
			cursor_y += 1;
			cursor_x = 0;
			str++;
			continue;
		}
		else if(*str == '\t'){
			cursor_x += 5;
			str++;
			continue;
		}
		int position = (cursor_y*VGA_WIDTH) + cursor_x;
		int vidAddress = VIDEO_START + (position * 2);
		*(char*)vidAddress = *str;
		uint16_t color = DEFAULT_COLOR;
		*(char*)(vidAddress+1) = color;
		str++;
		cursor_x += 1;
		if(cursor_x >= VGA_WIDTH){
			cursor_y += 1;
			cursor_x = 0;
		}
	}
	update_cursor();
	return (cursor_y*VGA_WIDTH) + cursor_x;
}

void cursor_enable(int cursor_start, int cursor_end){
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end); 
}
