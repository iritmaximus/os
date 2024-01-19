#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// TODO make this conforming to proper libc func
void print(const char* str)
{
	while (*str != '\0')
	{
		putchar(*str);
		str++;
	}
}

int printf(const char* restrict format, ...)
{
	va_list arg_list;
	va_start(arg_list, format);


	while(*format != '\0')
	{
		if (*format == '%') {
			format++;
			switch(*format)
			{
				case 'c':
					char c = (char) va_arg(arg_list, int);
					putchar(c);
					format++;
					break;
				case 's':
					char* str = va_arg(arg_list, char*);
					format++;
					print(str);
					break;
				case 'x':
					char* hex_str[33];
					int hex_value = va_arg(arg_list, int);
					itoa(hex_value, *hex_str, 16);
					print(*hex_str);
					format++;
					break;
				default:
					char* int_str[33];
					int int_value = va_arg(arg_list, int);
					itoa(int_value, *int_str, 2);
					print(*int_str);
					format++;
					break;
			}
        } 

		else
		{
			putchar(*format);
			format++;
			continue;
		}

	}
	va_end(arg_list);
	return 0;
}
