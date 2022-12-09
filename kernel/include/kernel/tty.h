#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H


#include <stdint.h>

void initialize_terminal();
void terminal_char(uint8_t color, char c);
void terminal_string(uint8_t color, char* c);
void test_terminal();


#endif
