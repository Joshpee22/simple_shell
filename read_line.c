#include "shellheader.h"
/**
 *free_args - the free a two dimensional strng
 *@args:array of ptr to strngs
 *Return:void
 */
void free_arg(char **arg)
{
	int x = 0;

	for (x = 0; arg[x]; x++)
	{
		free(arg[x]);
	}
	free(arg);
}
/**
 *read_line - read user input from standard input
 *
 *Return:ptr to strng containing user input
 */
char *read_line(void)
{
	char *lines = NULL;
	size_t len = 0;
	int var = 0;

	var = getline(&lines, &len, stdin);
	if (var == EOF)
	{
		free(lines);
		exit(0);
	}
	if (lines == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(lines);
		exit(-1);
	}

	return (lines);
}
