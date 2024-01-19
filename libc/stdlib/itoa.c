#include <stdio.h>

char* itoa(int value, char* str, int base)
{
	// check for incorrect base
	if (base < 2 || base > 36)
	{
		printf("\n ERROR: Incorrect base\n");
		return '\0';
	}

	char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";

	while (value/base > 1)
	{
		// TODO does this need a check for str_len?
		*str = num[value % base];
		str++;
		value /= base;
	}

	return str;
}
