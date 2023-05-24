#include "main.h"

/**
 * without_comment - delete comment from the inputs
 *
 * @in: input strngs
 * Return:the input without comment
 */
char *without_comment(char *inn)
{
	int x, up_to;

	up_to = 0;
	for (x = 0; inn[x]; x++)
	{
		if (inn[x] == '#')
		{
			if (x == 0)
			{
				free(inn);
				return (NULL);
			}

			if (inn[x - 1] == ' ' || inn[x - 1] == '\t' || inn[x - 1] == ';')
				up_to = x;
		}
	}

	if (up_to != 0)
	{
		inn = _realloc(inn, x, up_to + 1);
		inn[up_to] = '\0';
	}

	return (inn);
}

/**
 * shell_loop - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int loops, i_eof;
	char *input;

	loops = 1;
	while (loops == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loops = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loops = 0;
			free(input);
		}
	}
}
