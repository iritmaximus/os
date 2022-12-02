boot.o: boot.s
	i686-elf-as boot.s -o boot.o

kernel.o: kernel.c
	i686-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

link: boot.o kernel.o
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	var := $(shell grub-file --is-x86-multiboot myos.bin ; false)
	ifneq ($(.SHELLSTATUS),0)
  	$(error grub is not multiboot)
	endif

mkgrub: myos.bin grub.cfg
	cp myos.bin iso-build/boot/myos.bin
	cp grub.cfg iso_build/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso-build


compile: boot.s kernel.c linkder.ld
	i686-elf-as boot.s -o boot.o
	i686-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
	var := $(shell grub-file --is-x86-multiboot myos.bin ; false)
	ifneq ($(.SHELLSTATUS),0)
  	$(error grub is not multiboot)
	endif

clean:
	rm -rf *.o *.bin
