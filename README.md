# DEROS

This is my handwritten kernel made with the guidance from osdev as an educational project. This is
my second attempt at this because the first time I had problems with C and I burnt out on the project.

## Requirements
* Cross-compiled gcc (i686-elf)
    * https://wiki.osdev.org/GCC_Cross-Compiler
* Cross-compiled binutils (i686-elf)
    * https://wiki.osdev.org/GCC_Cross-Compiler
* Make
* Qemu with i386 support
* Grub with pc support (or multiboot or qemu, didn't try which one it was)
* Xorriso (`dev-libs/libisoburn` on Gentoo)

## Commands
* `make run`
    * Builds the project and tries to start it with qemu.
    * Requires cross-compiled gcc and binutils to build correctly.
* `make clean`
    * Removes all generated files
    * While developing this should be run each time before `make run` so all updates to the files get compiled.
