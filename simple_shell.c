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
int main(int  __attribute__((unused)) argc, char **argv,
		char __attribute__((unused)) **env)
{
	char *buf, *EXIT = "exit";
	size_t n = 0;
	ssize_t nread;
	int _stat, i, status = 0;
	pid_t pid;

	while (1)
	{
		buf = NULL;
		_stat = isatty(STDIN_FILENO);
		if (_stat == 1)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&buf, &n, stdin);
		if (nread == -1)
		{
			if (buf)
				free(buf);
			printf("Error, getline failed\n");
			return (1);
		}
		if (_parsecmd(buf, &argv) == -1)
		{
			if (buf)
				free(buf);
			printf("Error, _parsecmd failed\n");
			return (4);
		}
		if (buf)
			free(buf);
		printf("%s - %s\n", argv[0], EXIT);
		if (_strcmp(argv[0], EXIT) == 0)
		{
			printf("Exiting the shell...\n");
			if (argv[1])
				status = _atoi(argv[1]);
			for (i = 0; argv[i] != NULL; ++i)
				free(argv[i]);
			if (argv)
				free(argv);
			exit(status);
		}
		pid = fork();
		if (pid == -1)
		{
			printf("Error, fork failed\n");
			return (2);
		}
		if (pid == 0)
		{
			if (_execve(argv) == -1)
			{
				printf("Error, _execve failed\n");
				return (3);
			}
		}
		else
		{
			if (argv)
			{
				for (i = 0; argv[i] != NULL; ++i)
					free(argv[i]);
				free(argv);
			}
			wait(NULL);
		}
	}
	return (0);
}

