CC=i686-elf-gcc
AS=i686-elf-as
QEMU=qemu-system-i386
ARCH=i386

CFLAGS?=-ffreestanding -O2 -Wall -Wextra
CPPFLAGS?=-Iinclude -Iarch/$(ARCH)/include
LDFLAGS?=

ARCHDIR=arch/i386
KERNELDIR=kernel
ISODIR=isodir

OBJS=$(KERNELDIR)/kernel.o $(ARCHDIR)/tty.o boot.o

.PHONY: clean run clean
.SUFFIXES: .o .c .s

run: deros.iso
	$(QEMU) -cdrom deros.iso

.c.o:
	$(CC) -MD -c $< -std=gnu99 -o $@ $(CFLAGS) $(CPPFLAGS)

.s.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

deros.bin: $(OBJS)
	$(CC) -T linker.ld -o deros.bin $(CFLAGS) -nostdlib $(OBJS) -lgcc

isodir: deros.bin
	mkdir -p $(ISODIR)/boot/grub
	cp deros.bin $(ISODIR)/boot
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg

deros.iso: deros.bin isodir
	grub-mkrescue -o deros.iso isodir
	

clean:
	rm -f *.o *.bin *.iso *.d
	rm -f $(KERNELDIR)/*.o $(KERNELDIR)/*.d
	rm -f $(ARCHDIR)/*.o $(ARCHDIR)/*.d
	rm -rf isodir
