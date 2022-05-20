
int printAt(const char* str, int vidAddress){
	while(*str != '\0'){
		*(char*)vidAddress = *str;
		vidAddress+=2;
		str++;
	}
	return vidAddress;
}

/*void enable_cursor(int cursor_start, int cursor_end){
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);

	outb(0x3D4. 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_end);
}*/

extern void main(){
	int vidAddress = 0xb8000;
	vidAddress = printAt("Damn this works! ", vidAddress);	
	vidAddress = printAt("I can write multiple lines from C to here. ", vidAddress);
}
