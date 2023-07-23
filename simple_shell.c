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
        char *buf;
        size_t n = 0;
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
			if (buf)
				free(buf);
			printf("Error, getline failed\n");
			return (1);
		}
		_pathcheck(buf, environ);
		pid = fork();
		if (pid == -1)
		{
			free(buf);
			printf("Error, fork failed\n");
			return (2);
		}
		if (pid == 0)
		{
			if (_parsecmd(buf, &argv) == -1)
			{
				if (buf)
					free(buf);
				printf("Error, _parsecmd failed\n");
				return (4);
			}
			if (_execve(argv) == -1)
			{
				if (buf)
					free(buf);
				printf("Error, _execve failed\n");
				return (3);
			}
                }
                else
                {
                        wait(NULL);
                }
	}
	return (0);
}

