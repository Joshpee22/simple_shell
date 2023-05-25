#include "main.h"

/**
 * get_error - call the erros according the builtin, syntax or permissions
 * @datash: data struct that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datash, int e_val)
{
	char *erro;

	switch (e_val)
	{
	case -1:
		erro = error_env(datash);
		break;
	case 126:
		erro = error_path_126(datash);
		break;
	case 127:
		erro = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			erro = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			erro = error_get_cd(datash);
		break;
	}

	if (erro)
	{
		write(STDERR_FILENO, erro, _strlen(erro));
		free(erro);
	}

	datash->status = e_val;
	return (e_val);
}
