#include "main.h"

void _perror(char *s, shell_data *data, int status)
{
	if (s)
		printf("%s", s);
	free_shell_data(data);
	exit(status);
}
