all: Binaries/OS.bin

Binaries/OS.bin: Binaries/boot.bin Binaries/full_kernel.bin Binaries/zeroes.bin
	cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin" > "Binaries/OS.bin"

Binaries/full_kernel.bin: Binaries/kernel_entry.o Binaries/kernel.o
	i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" --oformat binary

Binaries/zeroes.bin: zeroes.asm
	nasm "zeroes.asm" -f bin -o "Binaries/zeroes.bin"

Binaries/kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -m32 -g -c "kernel.c" -o "Binaries/kernel.o"

Binaries/kernel_entry.o: kernel_entry.asm
	nasm "kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"

Binaries/boot.bin: boot.asm
	nasm "boot.asm" -f bin -o "Binaries/boot.bin"

.PHONY:
clean:
	rm Binaries/*
