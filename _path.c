#include "main.h"

char *_pathcheck(char __attribute__((unused)) *cmd, char **env)
{
	char *path, *pathdup, **pathtok;
	int i = 0;

	while (env[i])
		if (env[i][0] == 'P' && env[i++][3] == 'H')
			break;
	path = env[i];
	pathdup = strdup(path);
	if (pathdup == NULL)
		return NULL;

	printf("%s\n", pathdup);
	if (parsePATH(pathdup, &pathtok))
		printf("done");
	else
	{
		free(pathdup);
		return (NULL);
	}
	while (pathtok[i] != NULL)
		free(pathtok[i++]);
	free(pathtok);
	return NULL;
}

int parsePATH(char *path,char ***pathtok)
{
	char *token;
	int args = 0, i = 0;
	if (pathtok == NULL || path == NULL)
		return (0);
	
	while (path[i] != '\0')
		if (path[i++] == ':')
			args++;
	(*pathtok) = (char **) malloc(sizeof(char *) * (args + 2));

	if ((*pathtok) == NULL)
		return (0);

	token = strtok(path, "=");

	for (i = 0; i <= args; i++)
	{
		token = strtok(NULL, ":");
		(*pathtok)[i] = strdup(token);

		if ((*pathtok)[i] == NULL)
		{
			for (i = 0; (*pathtok)[i] != NULL; i++)
				free((*pathtok)[i]);
			free(*pathtok);
			return (0);
		}
	}
	(*pathtok)[i] = NULL;
	for (i = 0; i <= args; i++)
	{
		printf("%s\n", (*pathtok)[i]);
	}
	return (1);
}
