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
	free_shell_data(data);
	exit(status);
}

