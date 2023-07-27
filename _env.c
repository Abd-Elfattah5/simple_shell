#include "main.h"

/**
 * _env - function to print all the env variables
 * Return: none
 * @data: the data needed to print
 */
void _env(shell_data *data)
{
	int i = 0;

	while (data->_environ[i] != NULL)
	{
		printf("%s\n", data->_environ[i]);
		i++;
	}
}
