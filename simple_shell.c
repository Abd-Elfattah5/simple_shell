#include "main.h"
#include <errno.h>
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
		{
			write(STDOUT_FILENO, "($) ", 4);
		}
		if ((nread = getline(&buf, &n, stdin)) == -1)
		{
			free(buf);
			return (1);
		}
		if ((pid = fork()) == -1)
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
				{
					printf("%s: 1: %s: not found\n", argv[0], buf);
				}
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
