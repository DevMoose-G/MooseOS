#include <system.h>

void plotPixel(int x, int y){
	typedef unsigned char byte;
	byte* VGA = (byte*)0xA0000000L;
	unsigned short offset = 320*y + x;
	VGA[offset] = 0x09;
}

extern void main(){
	clr_screen();
	char* hpSnippet= "\tMr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much. They were the last people you'd expect to be involved in anything strange or mysterious, because they just didn't hold with such nonsense.\n\tMr. Dursley was the director of a firm called Grunnings, which made drills. He was a big, beefy man with hardly any neck, although he did have a very large mustache. Mrs. Dursley was thin and blonde and had nearly twice the usual amont of neck, which came in very useful as she spent so much of her time craning over garden fences, spying on the neighbors. The Dursleys had a small son called Dudley and in their opinion there was no finer boy anywhere.";
	char* snippet = hpSnippet+300;
	int vidAddress = VIDEO_START;
	cursor_enable(0, VGA_WIDTH);
	int pos = terminal_print(hpSnippet);	
	//plotPixel(8, 8);
	for(;;); // endless loop for kernel
}
