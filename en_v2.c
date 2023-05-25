#include "main.h"

/**
 * copy_info - copy info to create
 * a new env 
 * @name: the name (env or alias)
 * @value:the value (env or alias)
 *
 * Return: the new env or alias.
 */
char *copy_info(char *names, char *value)
{
	char *new;
	int length_name, len_value, len;

	length_name = _strlen(names);
	len_value = _strlen(value);
	len = length_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, names);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - set an env var
 *
 * @name:the name of the environment var
 * @value: the value of the environment var
 * @datash: data struct (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int f;
	char *var_env, *name_env;

	for (f = 0; datash->_environ[f]; f++)
	{
		var_env = _strdup(datash->_environ[f]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[f]);
			datash->_environ[f] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, f, sizeof(char *) * (f + 2));
	datash->_environ[f] = copy_info(name, value);
	datash->_environ[f + 1] = NULL;
}

/**
 * _setenv - compare env var names
 * with the name passed
 * @datash: data relevant (env name &env value).
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *data_sh)
{

	if (data_sh->args[1] == NULL || data_sh->args[2] == NULL)
	{
		get_error(data_sh, -1);
		return (1);
	}

	set_env(data_sh->args[1], data_sh->args[2], data_sh);

	return (1);
}

/**
 * _unsetenv - delete a env var
 *
 * @datash: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int f, j, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (f = 0; datash->_environ[f]; f++)
	{
		var_env = _strdup(datash->_environ[f]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = f;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (f));
	for (f = j = 0; datash->_environ[f]; f++)
	{
		if (f != k)
		{
			realloc_environ[j] = datash->_environ[f];
			j++;
		}
	}
	realloc_environ[j] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
