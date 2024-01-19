#ifndef _TTY_H
#define _TTY_H

#include <stdint.h>
#include <stddef.h>


void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void clear_line(size_t line);
void terminal_scroll(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_initialize(void);

#endif
