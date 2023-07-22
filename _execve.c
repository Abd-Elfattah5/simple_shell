#include "main.h"

int _execve(char **argv)
{
	int i;

	if (execve(argv[0], argv, NULL) == -1)
	{
		printf("Error, execve failed\n");
		for (i = 0; argv[i] != NULL; ++i)
			free(argv[i]);
		free(argv);
		/*if (errno == ENOENT)*/
			/*printf("%s: 1: %s: not found\n", argv[0], buf);*/
		return (-1);
	}
	return (0);
}
