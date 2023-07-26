#include "main.h"

void set_data(shell_data* data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->argc = 0;

	for (i = 0; environ[i] != NULL; ++i);

	data->_environ = malloc(sizeof(char *) * (i + 1));
	if (data->_environ == NULL)
	{
		printf("Error, malloc failed\n");
		return;
	}
	for (i = 0; environ[i] != NULL; ++i)
		data->_environ[i] = strdup(environ[i]);
	data->_environ[i] = NULL;
}
