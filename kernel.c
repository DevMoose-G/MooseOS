extern void cursor_enable(int cursor_start, int cursor_end);

int printAt(const char* str, int vidAddress){
	while(*str != '\0'){
		*(char*)vidAddress = *str;
		vidAddress+=2;
		str++;
	}
	return vidAddress;
}

extern void main(){
	int vidAddress = 0xb8000;
	cursor_enable(0, 15);
	vidAddress = printAt("Damn this works! ", vidAddress);	
	vidAddress = printAt("I can write multiple lines from C to here. ", vidAddress);
}
