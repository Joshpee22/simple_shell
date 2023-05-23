#include "shellheader.h"

/**
 * _occurence - return the number of occurences of a strng
 * @s:the string to check
 * Return: int
 */
unsigned int _occurence(char *n)
{
	int s, tmp = 0;

	for (s = 0; n[s] != '\0'; s++)
	{
		/*the test for all delimeters*/
		if (n[s]  == ' ' || n[s] == '\t' || n[s] == '\n')
			tmp++;
	}

	return (tmp);
}
/**
 *_strtotokens - split a sentence into multiple words.
 *@str: the string passed as argument.
 *Return: tokens
 */
char **_strtotokens(char *string)
{
	int n = 0;
	const char separator[] = " \t\n";
	int spaces = _occurence(string);
	char **tokens = malloc(sizeof(char *) * (spaces + 1));
	char *token;

	if (!tokens)
	{
		fprintf(stderr, "sh: allocation error\n");
		exit(1);
	}

	token = strtok(string, separator);

	while (token != NULL)
	{
		tokens[n] = token;
		token = strtok(NULL, separator);
		n++;
	}
	tokens[n] = NULL;
	return (tokens);
}
/**
 *check_file_status - checks whether a file exists
 *@filename:name of file
 *Return:0 - file is available, -1 otherwise
 */
int check_file_status(char *file_n)
{
	struct stat st;

	if (stat(file_n, &st) == -1)
		return (-1);
	return (0);
}
/**
 *_execute - executes a file given as input
 *@tokens:split tokens from stdin input
 *@line:line from stdin to free
 *Return:-1 (success), -1,otherwise
 */
int _execute(char **tokens, char *line, char *args)
{
	char *err1, *err2, *err3;
	pid_t cpid;
	int status;
	struct stat st;

	/*handle when token is a builtin cmd or NULL*/
	if (builtin_parser(tokens) == 0 || *tokens == NULL)
	{
		return (1);
	}
	/*fork the process*/
	cpid = fork();
	if (cpid < 0)
	{
		perror("Error:fork->-1");
		return (EXIT_FAILURE);
	}
/*child process*/
	if (cpid == 0)
	{
		if (stat(*tokens, &st) != 0)
		{
			get_path(tokens);
		}
		if (execve(tokens[0], tokens, NULL) == -1)
		{
			err1 = strcat(*tokens, ": No such file or directory\n");
			err2 = strcat(args, ":");
			err3 = strcat(err2, err1);
			write(STDERR_FILENO, err3, _strlen(err3));
			/*free(err1);*/
			/*free(err2);*/
			/*free(err3);*/
			free(line);
			free(tokens);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
wait(&status);
return (1);
}
