#include <system.h>

/* Defines an IDT entry */
struct idt_entry{
	unsigned short base_lo;
	unsigned short sel;	/* kernel segment goes here! 	*/
	unsigned char always0;	/* This will ALWAYS be set to 0!*/
	unsigned char flags;	/* Present, DPL, (01110)	*/
	unsigned short base_hi;
}__attribute__((packed));

struct idt_ptr{
	unsigned short limit;
	unsigned int base;
}__attribute__((packed));

// exists in boot.asm and is used to load IDT
extern void _idt_load();

/* Declares an IDT of 256 entries */
struct idt_entry idt[256];
struct idt_ptr _idtp;


// Use this function to set an entry in the IDT
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
	
}

// Installs the IDT
void idt_install(){
	// Sets the special IDT pointer up
	_idtp.limit = ( sizeof(struct idt_entry) * 256) -1;
	_idtp.base = &idt;
	
	// Clears out the entire IDT, initializing it to zeroes
	memset(&idt, 0, sizeof(struct idt_entry) * 256);
	
	// Adds any new ISRs to the IDT here using id_set_gate
	
	// Points the processor's internal register to the new IDT
	_idt_load();
}
