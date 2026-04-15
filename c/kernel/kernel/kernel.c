#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "tty.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error                                                                         \
    "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

size_t strlen(const char *str) {
  size_t len = 0;
  while (str[len])
    len++;
  return len;
}


void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_column = 0;
    if (++terminal_row == TERMINAL_HEIGHT) {
      terminal_scroll();
      terminal_row--;
    }
    return;
  }

  terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

  if (++terminal_column == TERMINAL_WIDTH) {
    terminal_column = 0;
    if (++terminal_row == TERMINAL_HEIGHT) {
      terminal_scroll();
      terminal_row--;
    }
  }
}

void terminal_write(const char *data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char *data) {
  terminal_write(data, strlen(data));
}

void terminal_test_scroll() {
  for (size_t i = 0; i < 126 - 65; i++) {
    terminal_putchar(i + 65);
    terminal_writestring("  more chars...\n");
  }
}

void kernel_main(void) {
  /* Initialize terminal interface */
  terminal_initialize();

  /* Newline support is left as an exercise. */

  terminal_test_scroll();
  terminal_writestring("Hello from the kernel :)\n");
}
