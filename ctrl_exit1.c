#include "shellheader.h"

/**
 *print_prompt - displays prompt before user input
 *
 *Return:void
 */
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	{
		_print("#cisfun$ ");
	}
}
/**
 *ctrl_c - supprss quitting when Control c is invoked
 *@signum:SIGINT variable
 *Return:void
 */
void ctrl_c(int signum)
{
	(void)signum;
	signal(SIGINT, ctrl_c);
	write(STDIN_FILENO, "\n#cisfun$ ", 11);
}
/**
 *shell_exit - exit a shell,taking into account different exit statuses
 *@args:the arguements passed
 *@line:the string to free
 *Return:void
 */
void shell_exit(char **arg, char *line)
{
	int status = 0;

	if (arg[1] != NULL)
	{
		status = atoi(arg[1]);
		if (status >= 0)
		{
			free(line);
			free(arg);
			exit(status);
		}
		printf("Exit: illegal status: %s\n", arg[1]);
	}
	else
	{
		free(line);
		free(arg);
		exit(0);
	}
}
