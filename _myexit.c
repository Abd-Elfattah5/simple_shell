#include "main.h"

/**
 * _myexit - exits the shell
 *
 * @data: shell_data
 */
void _myexit(shell_data *data)
{
	char ***argv = &data->args;
	int status = data->status;

	if ((*argv)[1])
		status = _atoi((*argv)[1]);
	if (status < 0)
	{
		dprintf(STDERR_FILENO, "%s: 1: exit: Illegal number: %i\n", data->av[0], status);
		status = 2;
	}
	free_shell_data(data);
	exit(status);
}

