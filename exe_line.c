#include "main.h"

/**
 * exec_line - find builtins & cmd
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(data_shell *datash)
{
	int (*builtins)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtins = get_builtin(datash->args[0]);

	if (builtins != NULL)
		return (builtins(datash));

	return (cmd_exec(datash));
}
