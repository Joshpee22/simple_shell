#include "main.h"

/**
 * swap_char - swap and & for non-printed characters
 *
 * @input: input strings
 * @bool: the type of swap
 * Return:the swapped string
 */
char *swap_char(char *input, int bool)
{
	int f;

	if (bool == 0)
	{
		for (f = 0; input[f]; f++)
		{
			if (input[f] == '|')
			{
				if (input[f + 1] != '|')
					input[f] = 16;
else
					f++;
			}

			if (input[f] == '&')
			{
				if (input[f + 1] != '&')
					input[f] = 12;
				else
					f++;
			}
		}
	}
	else
	{
		for (f = 0; input[f]; f++)
		{
			input[f] = (input[f] == 16 ? '|' : input[f]);
			input[f] = (input[f] == 12 ? '&' : input[f]);
		}
	}
	return (input);
}

/**
 * add_nodes - add separators and command lines in the lists
 *
 * @head_s: the head of separator list
 * @head_l: thrhead of command lines list
 * @input: the input str
 * Return: no return
 */
void add_nodes(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *lines;

	input = swap_char(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_end(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_end(head_s, input[i]);
			i++;
		}
	}

	lines = _strtok(input, ";|&");
	do {
		lines = swap_char(lines, 1);
		add_line_node_end(head_l, lines);
		lines = _strtok(NULL, ";|&");
	} while (lines != NULL);

}

/**
 * go_next - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loops_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loops_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loops_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loops_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loops_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loops_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commands - splits cmd line according to
 * the separators ;, | and &, and exe them
 *
 * @datash: data struct
 * @input: input strng
 * Return: 0 to exit, 1 to continue
 */
int split_commands(data_shell *datash, char *input)
{

	sep_list *heads, *list_s;
	line_list *head_l, *list_l;
	int loops;

	heads = NULL;
	head_l = NULL;

	add_nodes(&heads, &head_l, input);

	list_s = heads;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_line(datash->input);
		loops = exec_line(datash);
		free(datash->args);

		if (loops == 0)
			break;

		go_next(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_list(&heads);
	free_line_list(&head_l);

	if (loops == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenize the input strng
 *
 * @input: input strng.5
 * Return: string splitted.
 */
char **split_line(char *input)
{
	size_t bsize;
	size_t n;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (n = 1; token != NULL; n++)
	{
		if (n == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, n, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[n] = token;
	}

	return (tokens);
}
