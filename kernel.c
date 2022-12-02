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

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

size_t strlen(const char* str)
{
  size_t len = 0;
  while (str[len]) {
    len++;
  }
  return len;
};


/* converts colors to proper input for vga uint8_t [4bits fg, 4bits bg] */
static inline uint8_t make_vga_color(enum vga_color fg, enum vga_color bg)
{
  return fg | bg << 4;
}

/* converts colors and char to proper vga input uint16_t [8bits char, 8bits colors] */
static inline uint16_t make_vga_input(uint8_t color, char c)
{
  return (uint16_t) c | (uint16_t) color << 8;
}

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

  unsigned char test_char = 'H';
  uint8_t color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_LIGHT_RED);
  uint16_t test_byte = make_vga_input(color, test_char);

  terminal_char(color, 'H');
  for (size_t i=0; i < 100; i++) {
    terminal_char(color, 'i');
  }

  terminal_string(color, "Hiiiiiiiiiiii");
  terminal_string(color, " ");

  terminal_string(color, "\nMoo");
  terminal_string(color, "\nBebe");

}



void kernel_main(void)
{
  initialize_terminal();
  /* test_terminal(); */
  uint8_t color = make_vga_color(VGA_COLOR_WHITE, VGA_COLOR_BLUE);
  terminal_string(color, "Hi peips\nHih");
}
