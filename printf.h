#ifndef HOLBERTON_H
#define HOLBERTON_H

#include <stdarg.h>

int _putchar(char c);
int print_int(va_list arg);
int print_unsigned(va_list arg);
int _printf(const char *format, ...);
int print_char(va_list arg);
int print_str(va_list arg);

/**
 * struct identifierStruct - structure definition of a printTypeStruct
 * @indentifier: type
 * @printer: function to print
 */
typedef struct identifierStruct
{
char *indentifier;
int (*printer)(va_list);
} identifierStruct;

#endif
