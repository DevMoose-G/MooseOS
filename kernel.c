#include <system.h>

void* memset(void* dest, int val, int bytes){
	unsigned char* dest_chr = (unsigned char*) dest;
	unsigned char* dest_start = dest_chr;
	for(int i = 0; i < bytes; i++){
		*dest_chr = (char) val;
		dest_chr++;
	}
	return dest_start;
}

extern void main(){
	clr_screen();
	char* hpSnippet= "\tMr. and Mrs. Dursley, of number four, Privet Drive, were proud to say that they were perfectly normal, thank you very much. They were the last people you'd expect to be involved in anything strange or mysterious, because they just didn't hold with such nonsense.\n\tMr. Dursley was the director of a firm called Grunnings, which made drills. He was a big, beefy man with hardly any neck, although he did have a very large mustache. Mrs. Dursley was thin and blonde and had nearly twice the usual amont of neck, which came in very useful as she spent so much of her time craning over garden fences, spying on the neighbors. The Dursleys had a small son called Dudley and in their opinion there was no finer boy anywhere.";
	
	idt_install();
	cursor_enable(0, VGA_WIDTH);
	//int error = 9/0;

	int pos = terminal_print(hpSnippet);	

	for(;;); // endless loop for kernel
}
