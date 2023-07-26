#include "main.h"

char *_pathcheck(char *cmd, char **env)
{
	char *path_env, *pathdup, **pathtok, *path;
	int i = 0;

	while (env[i])
	{
		if (_strlen(env[i]) > 3)
		{
			if (env[i][0] == 'P' && env[i][3] == 'H')
				break;
		}
		i++;
	}
	path_env = env[i];
	pathdup = strdup(path_env);
	if (pathdup == NULL)
		return NULL;
	if (parsePATH(pathdup, &pathtok))
		_concatPATH(pathtok, &path, cmd);
	else
	{
		if (pathdup)
			free(pathdup);
		return (NULL);
	}
	i = 0;

	while (pathtok[i] != NULL)
		free(pathtok[i++]);
	free(pathtok[i]);
	free(pathtok);
	free(pathdup);
	return (path);
}


int parsePATH(char *path,char ***pathtok)
{
	char *token;
	int args = 0, i = 0, j = 0;
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
			for (j = 0; j <= i; j++)
				free((*pathtok)[j]);
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

int _concatPATH(char **pathtok, char **concated, char *cmd)
{
	char wd[256], cwd[256];
	int i = 0;
	struct stat buffer;

	if (pathtok == NULL)
		return (0);

	getcwd(cwd, 256);
	do
	{
		getcwd(wd, 256);
		if (!stat(cmd, &buffer))
		{
			
			if (!_strcat(wd, cmd, concated))
			{
				printf("couldn't concate");
				return (0);
			}
			else
				printf("the full path is %s\n", *concated);
			
		}
		chdir(pathtok[i]);
	}while (pathtok[++i] != NULL);
	chdir(cwd);
	return (1);
}

int _strcat(char *s1, char *s2, char **concated)
{
	int i = 0, j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);

	*concated = malloc(_strlen(s1) + _strlen(s2) + 2);
	
	if (*concated == NULL)
		return (0);
	while (s1[i] != '\0')
	{
		(*concated)[i] = s1[i];
		i++;
	}
	(*concated)[i++] = '/';

	while (s2[j] != '\0')
	{
		(*concated)[i + j] = s2[j];
		j++;
	}
	(*concated)[i + j] = '\0';

	printf("%s\n", *concated);
	return (1);
}
