#include "main.h"

/**
 * aux_help - Help info for the builtin help.
 * Return: no return
 */
void aux_help(void)
{
	char *aux = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, aux, _strlen(aux));
	aux = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, aux, _strlen(aux));
	aux = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, aux, _strlen(aux));
}
/**
 * aux_help_alias - Help info for the builtin alias.
 * Return: no return
 */
void aux_help_alias(void)
{
	char *aux = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, aux, _strlen(aux));
	aux = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, aux, _strlen(aux));
}
/**
 * aux_help_cd - Help info for the builtin alias.
 * Return: no return
 */
void aux_help_cd(void)
{
	char *aux = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, aux, _strlen(aux));
	aux = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, aux, _strlen(aux));
}
