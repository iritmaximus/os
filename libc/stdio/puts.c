#include <stdio.h>

int puts(const char* str)
{
	while (*str != '\0') {
		putchar(*str);
		str++;
	}
	putchar('\n');
	return (int) str;
}
