#include "main.h"

/**
 * repeated_char - counts the repetitions of a character
 *
 * @input: input string
 * @i: index string
 * Return: repetitions of strings
 */
int repeated_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int error_sep_op(char *input, int i, char last)
{
	int temp;

	temp = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			temp = repeated_char(input, 0);
			if (temp == 0 || temp > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			temp = repeated_char(input, 0);
			if (temp == 0 || temp > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_error - prints when a syntax error is found
 *
 * @datash: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control message error
 * Return: no return
 */
void print_syntax_error(data_shell *datash, char *input, int i, int bool)
{
	char *tmp, *tmp2, *tmp3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			tmp = (input[i + 1] == ';' ? ";;" : ";");
		else
			tmp = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		tmp = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		tmp = (input[i + 1] == '&' ? "&&" : "&");

	tmp2 = ": Syntax error: \"";
	tmp3 = "\" unexpected\n";
	counter = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(counter);
	length += _strlen(tmp) + _strlen(tmp2) + _strlen(tmp3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, datash->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, tmp2);
	_strcat(error, tmp);
	_strcat(error, tmp3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to
 * find and print a syntax error
 *
 * @datash: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int j = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syntax_error(datash, input, begin, 0);
		return (1);
	}

	j = error_sep_op(input + begin, 0, *(input + begin));
	if (j != 0)
	{
		print_syntax_error(datash, input, begin + j, 1);
		return (1);
	}

	return (0);
}
