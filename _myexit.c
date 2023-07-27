#include "main.h"

/**
 * _myexit - exits the shell
 *
 * @data: shell_data
 */
void _myexit(shell_data *data)
{
	char ***argv = &data->args;
	int status = data->status, i, is_string = 0;

	for (i = 0; data->args[1][i] != '\0'; ++i)
	{
		if (data->args[1][i] < '0' || data->args[1][i] > '9')
		{
			dprintf(STDERR_FILENO, "%s: 1: exit: Illegal number: %s\n", data->av[0], data->args[1]);
			status = 2;
			is_string = 1;
			break;
		}
	}
	if (!is_string)
	{
		if ((*argv)[1])
			status = _atoi((*argv)[1]);
	}
	if (status < 0)
	{
		dprintf(STDERR_FILENO, "%s: 1: exit: Illegal number: %i\n", data->av[0], status);
		status = 2;
	}
	free_shell_data(data);
	exit(status);
}

