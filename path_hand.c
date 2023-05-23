#include "shellheader.h"

/**
 *get_path - get the absolutes paths of a command
 *@args:ptr to an arrays of strngs
 *Return:the address of the path
 */
int get_path(char **argc)
{
	char *path, *toks, *cd_token;
	struct stat st;

	path = get_env("PATH");
	toks = strtok(path, ":");

	while (toks != NULL)
	{
		cd_token = cmd_build(*argc, toks);
		if (stat(cd_token, &st) == 0)
		{
			*argc = _strdup(cd_token);
			free(cd_token);
			free(path);
			return (0);
		}
		free(cd_token);
		toks = strtok(NULL, ":");
	}
	free(path);
	return (1);
}
/**
 *get_env - retrieves an environment variable
 *@path:variable passed
 *Return:pointer to a string
 */
char *get_env(char *path)
{
	char *envcpy;
	int i = 0;
	int len, len2;

	while (environ[i])
	{
		len = _strlen(path);
/*locate substring PATH*/
		if (strstr(environ[i], path))
		{
			if (environ[i][len] == '=')
			{
				len2 = _strlen(environ[i]) - _strlen(path);
				envcpy = malloc(sizeof(char) * len2);
				if (envcpy == NULL)
				{
					perror("Error: Insufficient memory");
					exit(1);
				}
				_strcpy(envcpy, environ[i] + (len + 1));
				return (envcpy);
			}
		}
		i++;
	}
	return (NULL);
}
/**
 *cmd_build - returns full cmd path
 *@token:cmd passed
 *@dir_value:current path dir
 *Return:pointer to full cmd path
 */
char *cmd_build(char *token, char *dir_value)
{
	size_t path_len;
	char *path;

	path_len = _strlen(token) + _strlen(dir_value) + 2;
	path = malloc(sizeof(char) * path_len);

	if (path == NULL)
	{
		perror("Error: malloc->buildcmd\n");
		return (NULL);
	}
	memset(path, 0, path_len);

	path = _strcat(path, dir_value);
	path = _strcat(path, "/");
	path = _strcat(path, token);
	return (path);
}
