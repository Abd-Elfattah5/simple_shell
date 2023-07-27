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
	int status;

	set_data(&data, argv);
	while (1)
	{
		if (_getcmd(&data) == 0)
			continue;
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
			_execve(&data);
		else
		{
			free_in_buffers(&data);
			wait(&status);
			data.status = WEXITSTATUS(status);
		}
	}
	return (0);
}

