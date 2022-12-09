#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>



/* Check if the compiler thinks you are targeting the wrong operating system. */
/* #if defined(__linux__) */
/* #error "You are not using a cross-compiler, you will most certainly run into trouble" */
/* #endif */

/* /1* This tutorial will only work for the 32-bit ix86 targets. *1/ */
/* #if !defined(__i386__) */
/* #error "This tutorial needs to be compiled with a ix86-elf compiler" */
/* #endif */


size_t strlen(const char* str)
{
  size_t len = 0;
  while (str[len]) {
    len++;
  }
  return len;
};






void kernel_main(void)
{
  initialize_terminal();
  /* test_terminal(); */
  uint8_t color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
  terminal_string(color, "Hi peips\nHeh");
}
