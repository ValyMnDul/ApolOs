all: boot.bin

boot.bin: boot.asm
	nasm -f bin boot.asm -o boot.bin

clear:
	rm -f boot.bin

run: 
	qemu-system-x86_64 -drive format=raw,file=boot.bin
