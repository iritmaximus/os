#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include <kernel/tty.h>

#include "vga.h"

static const size_t VGA_HEIGHT = 25;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_BUFFER_ADDR = 0xB8000;



uint8_t vga_column;
uint8_t vga_row;
uint16_t* vga_buffer_addr;
uint8_t blank_color;


void initialize_terminal()
{
  vga_column = 0;
  vga_row = 0;
  vga_buffer_addr = (uint16_t*) VGA_BUFFER_ADDR;
  blank_color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

  uint16_t empty_char = make_vga_input(blank_color, ' ');

  for (size_t i = 0; i < VGA_HEIGHT; i++) {
    for (size_t j = 0; j < VGA_WIDTH; j++) {
      vga_buffer_addr[i*VGA_HEIGHT + j] = empty_char;
    }
  }
}

void terminal_char(uint8_t color, char c)
{
  if (c == '\n') {
    vga_row++;
    vga_column = 0;
    return;
  }
  uint16_t vga_input = make_vga_input(color, c);
  uint16_t index = vga_column + vga_row * VGA_WIDTH;
  vga_buffer_addr[index] = vga_input;
  if (++vga_column > VGA_WIDTH) {
    vga_column = 0;
    if (++vga_row > VGA_HEIGHT) {
      vga_row = 0;
    }
  }
}

void terminal_string(uint8_t color, char* c)
{
  uint16_t len = strlen(c);
  for (size_t i = 0; i<len; i++) {
    terminal_char(color, c[i]);
  }
}






void test_terminal()
{
  vga_buffer_addr = (uint16_t*) 0xB8000;
  uint8_t color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_RED);

  terminal_char(color, 'H');
  for (size_t i=0; i < 100; i++) {
    terminal_char(color, 'i');
  }

  terminal_string(color, "Hiiiiiiiiiiii");
  terminal_string(color, " ");

  terminal_string(color, "\nMee");
  terminal_string(color, "\nBebe");
}
