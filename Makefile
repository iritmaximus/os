CC=i686-elf-gcc
AS=i686-elf-as
QEMU=qemu-system-i386

boot.o:
	$(AS) boot.s -o boot.o

kernel.o:
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

deros.bin: boot.o kernel.o
	$(CC) -T linker.ld -o deros.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

isodir: deros.bin
	mkdir -p isodir/boot/grub
	cp deros.bin isodir/boot
	cp grub.cfg isodir/boot/grub

deros.iso: deros.bin isodir
	grub-mkrescue -o deros.iso isodir

run: deros.iso
	$(QEMU) -cdrom deros.iso

clean:
	rm *.o *.bin *.iso
	rm -r isodir
