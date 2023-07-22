#include "main.h"

int _parsecmd(char *cmd, char ***argv)
{
	char *token = NULL, *cmd_cpy = NULL, *delim = " \n";
	int argc = 1, i = 0;

	cmd_cpy = strdup(cmd);
	if (cmd_cpy == NULL)
	{
		printf("Error, strdup failed\n");
		return (-1);
	}
	token = strtok(cmd, delim);
	while(token)
	{
		token = strtok(NULL, delim);
		argc++;
	}
	*argv = (char **)malloc(sizeof(char *) * argc);
	if (*argv == NULL)
	{
		printf("Error, malloc failed\n");
		free(cmd_cpy);
		return (-1);
	}
	token = strtok(cmd_cpy, delim);
	for (i = 0; token != NULL; ++i)
	{
		(*argv)[i] = strdup(token);
		if ((*argv)[i] == NULL)
		{
			printf("Error, strdup2 failed\n");
			for (i = 0; (*argv)[i] != NULL; ++i)
				free((*argv)[i]);
			free(*argv);
			free(cmd_cpy);
			return (-1);
		}
		token = strtok(NULL, delim);
	}
	(*argv)[i] = NULL;
	/*for (i = 0; (*argv)[i] != NULL; i++)*/
		/*printf("%s\n", (*argv)[i]);*/
	free(cmd_cpy);
	return (0);
}
