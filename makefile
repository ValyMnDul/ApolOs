all: image.bin

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

kernel.o: kernel.c
	gcc -m32 -ffreestanding -fno-pie -fno-pic -mgeneral-regs-only -c kernel.c -o kernel.o

kernel.bin: kernel.o
	ld -m elf_i386 -Ttext 0x1000 --oformat binary kernel.o -o kernel.bin

image.bin: boot.bin kernel.bin
	cat boot.bin kernel.bin > image.bin

clear:
	rm -f *.bin *.o

run: 
	qemu-system-x86_64 -drive format=raw,file=image.bin