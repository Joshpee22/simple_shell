#include "shellheader.h"
/**
 *get_history - fills all files with user inputs
 *@input:user inputs
 *Return:0 - success,-1 otherwise
 */
int get_history(char *inputs)
{
	int len = 0;
	char *file_n = "/.simple_shell_history";
	char *directory = get_env("HOME");
	char *file_path = malloc(_strlen(directory) + _strlen(file_n) + 1);
	if (!file_path)
	{
		perror("malloc error->get_history");
		free(directory);
		return (-1);
	}
	_strcpy(file_path, directory);
	_strcpy(file_path, file_n);
	ssize_t fd, w;

/*if not exist create,read and write and append if exist*/
	fd = open(file_path, O_CREAT | O_RDWR | O_APPEND, 0600);
	if (fd < 0)
		return (-1);
	if (inputs)
	{
		while (inputs[len])
			len++;
		w = write(fd, inputs, len);
		if (w < 0)
			return (-1);
	}
	free(file_path);
	free(directory);
	return (1);
}
/**
 *display_history - display user's history
 *
 *Return:0 (success), -1 otherwise
 */
int display_history(void)
{
	char *files_n = "/.simple_shell_history";
	char *directory = get_env("HOME");
	char *file_path = malloc(_strlen(files_n) + _strlen(directory) + 1);
	char *line = NULL;
	size_t len;
	FILE *fp;
	int counter = 0;
	if (!file_path)
	{
		perror("malloc error->display_history");
		free(directory);
		return (-1);
	}
	_strcpy(file_path, directory);
	_strcpy(file_path, files_n);
	fp = fopen(file_path, "r");
	if (fp == NULL)
	{
		return (-1);
	}
	while ((getline(&line, &len, fp)) != -1)
	{
		counter++;
		printf("%d %s", counter, line);
	}
	if(line != NULL)
		free(line);
	fclose(fp);
	free(file_path);
	free(directory);
	return (0);
}
