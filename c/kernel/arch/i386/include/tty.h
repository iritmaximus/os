#ifndef TTY_H
#define TTY_H

#include <stddef.h>
#include <stdint.h>

#include "vga.h"

static size_t TERMINAL_WIDTH = VGA_WIDTH;
static size_t TERMINAL_HEIGHT = VGA_HEIGHT;

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t *terminal_buffer;

void terminal_setcolor(uint8_t color);
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
void terminal_clear_row(size_t row);
void terminal_scroll(void);
void terminal_initialize(void);
void terminal_initialize2(void);

#endif
