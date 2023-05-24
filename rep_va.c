#include "main.h"

/**
 * check_env - check if the type variables is an env variable
 *
 * @h: the head of linked lists
 * @in: the input string
 * @data: the data struct
 * Return: no return
 */
void check_env(r_var **h, char *in, data_shell *data)
{
	int roll, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (roll = 0; _envr[roll]; roll++)
	{
		for (j = 1, chr = 0; _envr[roll][chr]; chr++)
		{
			if (_envr[roll][chr] == '=')
			{
				lval = _strlen(_envr[roll] + chr + 1);
				add_rvar_node(h, j, _envr[roll] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[roll][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_rvar_node(h, j, NULL, 0);
}

/**
 * check_vars - check if the type var is $$ or $
 *
 * @h: the head of the linked lists
 * @in: the inpust strng
 * @st:the last status of the Shell
 * @data: the data struct
 * Return: no return
 */
int check_vars(r_var **h, char *in, char *st, data_shell *data)
{
	int n, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (n = 0; in[n]; n++)
	{
		if (in[n] == '$')
		{
			if (in[n + 1] == '?')
				add_rvar_node(h, 2, st, lst), n++;
			else if (in[n + 1] == '$')
				add_rvar_node(h, 2, data->pid, lpd), n++;
			else if (in[n + 1] == '\n')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == '\0')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == ' ')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == '\t')
				add_rvar_node(h, 0, NULL, 0);
			else if (in[n + 1] == ';')
				add_rvar_node(h, 0, NULL, 0);
			else
				check_env(h, in + n, data);
		}
	}

	return (n);
}

/**
 * replaced_input - replaces strng into var
 *
 * @head: the head of the linked lists
 * @input: input strngs
 * @new_input: new inputs strngs (replaced)
 * @nlen: new len
 * Return:the replaced strngs
 */
char *replaced_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int f, j, k;

	indx = *head;
	for (j = f = 0; f < nlen; f++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[f] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				f--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[f] = indx->val[k];
					f++;
				}
				j += (indx->len_var);
				f--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[f] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_var - call funcs to replace strng into variables
 *
 * @input:the input strngs
 * @datash: the data struct
 * Return: the replaced strng
 */
char *rep_var(char *input, data_shell *datash)
{
	r_var *head, *tmp;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoa(datash->status);
	head = NULL;

	olen = check_vars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	tmp = head;
	nlen = 0;

	while (tmp != NULL)
	{
		nlen += (tmp->len_val - tmp->len_var);
		tmp = tmp->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replaced_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_rvar_list(&head);

	return (new_input);
}
