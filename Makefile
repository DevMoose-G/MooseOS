export PATH := /usr/local/i386elfgcc/bin:$(PATH)
all: Binaries/OS.bin

Binaries/OS.bin: Binaries/boot.bin Binaries/full_kernel.bin Binaries/zeroes.bin
	cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin" > "Binaries/OS.bin"

Binaries/full_kernel.bin: Binaries/kernel_entry.o Binaries/kernel.o Binaries/func.o Binaries/screen.o
	i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x1000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/func.o" "Binaries/screen.o" --oformat binary

Binaries/zeroes.bin: zeroes.asm
	nasm "zeroes.asm" -f bin -o "Binaries/zeroes.bin"

Binaries/kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -m32 -g -I./include -c "kernel.c" -o "Binaries/kernel.o"

Binaries/screen.o: screen.c
	i386-elf-gcc -ffreestanding -m32 -g -I./include -c "screen.c" -o "Binaries/screen.o"

Binaries/func.o: func.asm
	nasm "func.asm" -f elf -o "Binaries/func.o"

Binaries/kernel_entry.o: kernel_entry.asm
	nasm "kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"

Binaries/boot.bin: boot.asm
	nasm "boot.asm" -f bin -o "Binaries/boot.bin"

.PHONY:
clean:
	rm Binaries/*
