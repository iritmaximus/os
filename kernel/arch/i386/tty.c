#include <string.h>

#include <kernel/tty.h>
#include "vga.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
 
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer = VGA_MEMORY;


void terminal_setcolor(uint8_t color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void clear_line(size_t line)
{
	char c = ' ';
	for (size_t column = 0; column < VGA_WIDTH; column++)
		terminal_putentryat(c, terminal_color, column, line);
}

void terminal_scroll(void) 
{
	// starting from the second row, iterate through the chars in the buffer and add them
	// one row "above"
	for (size_t read_height = 1; read_height < VGA_HEIGHT; read_height++) {
		clear_line(read_height - 1);
		for (size_t read_width = 0; read_width < VGA_WIDTH; read_width++) {
			// index to read the char from
			size_t read_index = read_height * VGA_WIDTH + read_width;
			size_t input_index = (read_height - 1) * VGA_WIDTH + read_width;

			terminal_buffer[input_index] = terminal_buffer[read_index];
		}
	}
	
	clear_line(VGA_HEIGHT - 1);
	terminal_column = -1;
	terminal_row = VGA_HEIGHT - 1;
}
 
void terminal_putchar(char c) 
{
	if (terminal_row == VGA_HEIGHT)
		terminal_scroll();

	// checks for newlines and moves the "cursor" to the beginning of next line
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column > VGA_WIDTH) {
		terminal_column = 0;
		terminal_row++;
	}

}

 
void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

