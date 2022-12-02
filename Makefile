all: mkgrub



boot.o: boot.s
	i686-elf-as boot.s -o boot.o

kernel.o: kernel.c
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

myos.bin: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

myos.iso: myos.bin
	cp myos.bin iso-build/boot/myos.bin
	cp grub.cfg iso-build/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso-build


run: myos.iso
	qemu-system-i386 -cdrom myos.iso

clean:
	rm -rf *.o *.bin
