#include "main.h"

/**
 * read_line - read the inputs strng.
 *
 * @i_eof: return value of getline func
 * Return: input strng
 */
char *read_line(int *i_eof)
{
	char *tmp = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&tmp, &bufsize, stdin);

	return (tmp);
}
