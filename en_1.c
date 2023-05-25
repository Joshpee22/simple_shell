#include "main.h"

/**
 * cmp_env_name - compare env var name
 * with the name passe
 * @nenv: the name of the environment var
 * @name: name passe
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int f;

	for (f = 0; nenv[f] != '='; f++)
	{
		if (nenv[f] != name[f])
		{
			return (0);
		}
	}

	return (f + 1);
}

/**
 * _getenv - get an environment var
 * @name: name of the env var
 * @_environ: environment var
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int n, move;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (n = 0; _environ[n]; n++)
	{
		/* If name and env are equal */
		move = cmp_env_name(_environ[n], name);
		if (move)
		{
			ptr_env = _environ[n];
			break;
		}
	}

	return (ptr_env + move);
}

/**
 * _env - print the env var
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int n, j;

	for (n = 0; datash->_environ[n]; n++)
	{

		for (j = 0; datash->_environ[n][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[n], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
