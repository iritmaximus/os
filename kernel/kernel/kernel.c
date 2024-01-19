#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/paging.h>


/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
	printf("Initializing kernel...\n");
 
	/* Initializing paging for the os */
	init_paging();
	printf("* Paging initialized\n");

	printf("\n");
	printf("Trying things out...\n");
	printf("Testing char: %c\n", 'b');
	printf("Testing string: %s\n", "hello");
	printf("Testing hex: %x\n", 10);
	printf("Testing int: %d\n", 10);
}
