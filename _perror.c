#include "main.h"
/**
 * _perror - function to print a message after error,
 * free the data in the struct and exit with a certain state
 * Return: non
 * @s: the message to be printed
 * @data: the data to be freed
 * @status: the state to exit with
*/
void _perror(char *s, shell_data *data, int status)
{
	if (s)
		printf("%s", s);
	free_shell_data(data);
	exit(status);
}
