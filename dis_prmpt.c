#include "shellheader.h"

/**
 *main - displays a prompt then wait for the end_user to enter a command
 *Return: 0 on success
 */
int main(int arg, char *argv[])
{
	(void)arg;
	char **toks;
	char *line;
	int stat;
	struct stat st;

	signal(SIGINT, ctrl_c);
	if (fstat(0, &st) == -1)
		perror("fstat");
	stat = 1;
	do {
/*print prompt if command is not piped*/
		print_prompt();
/*read input from stdin*/
		line = read_line();
		if (_strcmp(line, "\n") == 0)
		{
			toks = NULL;
			free(line);
			continue;
		}
		get_history(line);
/*split all the lines into toks*/
		toks = _strtotokens(line);
		if (toks[0] == NULL)
		{
			free(toks);
			free(line);
			continue;
		}
/*handle exit invokation*/
		if (_strcmp(toks[0], "exit") == 0)
		{
			shell_exit(toks, line);
		}
		else
		{
/*execute commands*/
			stat = _execute(toks, line, argv[0]);
		}
/*free memory*/
		free(line);
		free(toks);
	} while (stat == 1);
	return (stat);
}
