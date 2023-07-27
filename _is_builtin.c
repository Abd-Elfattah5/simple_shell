#include "main.h"

/**
 * _is_builtin - check if the command is built in
 *
 * @av: arguments list
 * Return: pointer to function
 */
void (*_is_builtin(char **av))(shell_data * data)
{
	int i;
	builtin_t F[] = {
		{"exit", _myexit},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"env", _env},
		{"cd", _cd},
		{NULL, NULL
		}};

	for (i = 0; F[i].name != NULL; ++i)
	{
		if (_strcmp(av[0], F[i].name) == 0)
			return (F[i].fun);
	}
	return (NULL);
}

