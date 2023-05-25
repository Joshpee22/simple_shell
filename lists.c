#include "main.h"

/**
 * add_sep_node_end - adds a separator found at the end
 * of a sep_list.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *nwe, *mal;

	nwe = malloc(sizeof(sep_list));
	if (nwe == NULL)
		return (NULL);

	nwe->separator = sep;
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
 * free_sep_list - frees a sep_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_sep_list(sep_list **head)
{
	sep_list *mal;
	sep_list *flur;

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

/**
 * add_line_node_end - adds a command line at the end
 * of a line_list.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *nwe, *mal;

	nwe = malloc(sizeof(line_list));
	if (nwe == NULL)
		return (NULL);

	nwe->line = line;
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
 * free_line_list - frees a line_list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *mal;
	line_list *flur;

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
