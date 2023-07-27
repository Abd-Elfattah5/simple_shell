#include "main.h"
/**
 * set_data - set shell data
 * Return: non
 * @data: the struct data to be filled
 * @av: the array of strings to be copied
*/
void set_data(shell_data *data, char **av)
{
	unsigned int i;

	data->av = av;
	data->input = NULL;
	data->args = NULL;
	data->status = 0;
	data->argc = 0;
	data->fd = NULL;

	for (i = 0; environ[i] != NULL; ++i)
		;
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
