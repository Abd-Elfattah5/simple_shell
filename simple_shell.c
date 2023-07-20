#include "main.h"
/**
 * main - Starting poing for the shell
 *
 * __attribute__((unused)) - annotations are used to suppress compiler warnings
 * about these unused parameters.
 * @argc: number of attributes
 * @argv: attributes list
 * @env: environment variable
 * Return: (0) on success, else otherwise
 */
int main(int  __attribute__((unused)) argc,
		char __attribute__((unused)) **argv,
		char __attribute__((unused)) **env)
{
	char *buf;
	size_t n;
	ssize_t nread;
	int _stat;
	pid_t pid;

	while (1)
	{
		_stat = isatty(STDIN_FILENO);
		if (_stat == 1)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&buf, &n, stdin);
		if (nread == -1)
		{
			free(buf);
			return (1);
		}
		pid = fork();
		if (pid == -1)
		{
			free(buf);
			return (2);
		}
		if (pid == 0)
		{
			buf = strtok(buf, "\n");
			if (execve(buf, argv, NULL) == -1)
			{
				if (errno == ENOENT)
					printf("%s: 1: %s: not found\n", argv[0], buf);

				free(buf);
				return (3);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	free(buf);
	return (0);
}
