#include "main.h"
/**
 * main - Starting poing for the shell
 *
 * __attribute__((unused)) - annotations are used to suppress compiler warnings
 * about these unused parameters.
 * @argc: number of attributes
 * @argv: attributes list
 * Return: (0) on success, else otherwise
 */
int main(int __attribute__((unused)) argc, char **argv)
{
	shell_data data;
	pid_t pid;
	void (*builtin)(shell_data *);

	set_data(&data, argv);
	while (1)
	{
		if (_getcmd(&data.input) == -1)
			_perror(NULL, &data, 0);
		if (_parsecmd(&data) == -1)
			_perror("Error, _parsecmd failed\n", &data, 2);
		builtin = _is_builtin(data.args);
		if (builtin)
		{
			builtin(&data);
			free_in_buffers(&data);
			continue;
		}
		if (!_pathcheck(&data))
		{
			printf("%s: 1: %s: command not found\n", argv[0], data.input);
			free_in_buffers(&data);
			continue;
		}
		pid = fork();
		if (pid == -1)
			_perror("Error, fork failed\n", &data, 3);
		if (pid == 0)
		{
			if (_execve(&data) == -1)
				_perror("Error, _execve failed\n", &data, 4);
		}
		else
		{
			free_in_buffers(&data);
			wait(NULL);
		}
	}
	return (0);
}

