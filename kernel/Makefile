GCC_COMP:=i686-elf-gcc
AS_COMP:=i686-elf-as
GRUB_COMP:=grub-mkrescue
QEMU:=qemu-system-i386


DESTDIR?=sysroot
KERNELDIR:=kernel/kernel
ARCHDIR:=kernel/arch


BOOT_FLAGS:=$(ARCHDIR)/boot.s -o boot.o
KERNEL_FLAGS:=-c $(KERNELDIR)/kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LINKER_FLAGS:=-T $(ARCHDIR)/linker.ld -o $(DESTDIR)/myos.bin -ffreestanding -O2 -nostdlib $(ARCHDIR)/boot.o kernel.o -lgcc
QEMU_FLAGS:=-cdrom $(DESTDIR)/myos.iso


boot.o: boot.s
	$(AS_COMP) $(BOOT_FLAGS)

kernel.o: kernel.c
	$(GCC_COMP) $(KERNEL_FLAGS)

myos.bin: boot.o kernel.o
	$(GCC_COMP) $(LINKER_FLAGS)

myos.iso: myos.bin
	mkdir -p $(DESTDIR)/boot/
	cp myos.bin $(DESTDIR)/boot/myos.bin
	cp grub.cfg $(DESTDIR)/boot/grub.cfg
	grub-mkrescue -o $(DESTDIR)/myos.iso $(DESTDIR)

run: myos.iso
	$(QEMU) $(QEMU_FLAGS)

clean:
	rm -rf *.o *.bin *.iso
