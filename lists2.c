#include "main.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *nwe, *mal;

	nwe = malloc(sizeof(r_var));
	if (nwe == NULL)
		return (NULL);

	nwe->len_var = lvar;
	nwe->val = val;
	nwe->len_val = lval;

	nwe->next = NULL;
	mal = *head;

	if (mal == NULL)
	{
		*head = nwe;
	}
	else
	{
		while (mal->next != NULL)
			mal = mal->next;
		mal->next = nwe;
	}

	return (*head);
}

/**
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_var **head)
{
	r_var *mal;
	r_var *flur;

	if (head != NULL)
	{
		flur = *head;
		while ((mal = flur) != NULL)
		{
			flur = flur->next;
			free(mal);
		}
		*head = NULL;
	}
}
