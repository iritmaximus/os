#include "tty.h"
#include "vga.h"

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * TERMINAL_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_setcolor(uint8_t color) { terminal_color = color; }

void terminal_clear_row(size_t row) {
  for (size_t i = 0; i < TERMINAL_WIDTH; i++)
    terminal_putentryat(' ', terminal_color, i, row);
}

void terminal_scroll(void) {
  for (size_t i = 0; i < TERMINAL_HEIGHT; i++) {
    for (size_t j = 0; j < TERMINAL_WIDTH; j++)
      terminal_buffer[i * TERMINAL_WIDTH + j] =
          terminal_buffer[(i + 1) * TERMINAL_WIDTH + j];
  }

  terminal_clear_row(TERMINAL_HEIGHT - 1);
}

void terminal_initialize(void) {
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t *)0xB8000;
  for (size_t y = 0; y < TERMINAL_HEIGHT; y++) {
    for (size_t x = 0; x < TERMINAL_WIDTH; x++) {
      const size_t index = y * TERMINAL_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}
