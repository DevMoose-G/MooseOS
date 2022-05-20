#define VGA_WIDTH 80
#define VIDEO_START 0xb8000

extern void outb(int port, int data);
extern int inb(int port);

void update_cursor(int x, int y){
	int pos = y * VGA_WIDTH + x;
	
	outb(0x3D4, 0x0F);
	outb(0x3D5, (int) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (int) ((pos >> 8) & 0xFF));
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
	int vidAddress = 0xb8000;
	cursor_enable(0, 25);
	vidAddress = printAt("Damn this works! ", vidAddress);	
	vidAddress = printAt("I can write multiple lines from C to here. ", vidAddress);
}
