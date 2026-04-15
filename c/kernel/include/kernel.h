#ifndef KERNEL_H
#define KERNEL_H

#include <stddef.h>
#include <stdint.h>

void terminal_initialize(void);
void terminal_write(const char *data, size_t size);
void terminal_writestring(const char *data);
void kernel_main(void);

#endif
