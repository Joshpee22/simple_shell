#include "shellheader.h"

/**
 * _putchar - write the char c to stdout
 * @c: This is the char to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and erro is set appropriately.
 */
int _putchar(char n)
{
return (write(1, &n, 1));
}

/**
 * _print - prints a strng
 * @str: pointer to the strng to print
 * Return: void
 */
void _print(char *string)
{
int n = 0;
while (string[n])
{
_putchar(string[n]);
n++;
}
}
