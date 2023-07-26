#include "main.h"
/**
 * _pathcheck - function to check on path and claim it if possible
 * Return: 1 if found and claimed and 0 otherwise
 * @data: all the data needed in shell_data struct
 */

int _pathcheck(shell_data *data)
{
	char *path_env, *pathdup, **pathtok, *path,
	     *cmd = data->input, **env = data->_environ;
	int i = 0, j = 0;

	while (data->args[0][j] != '\0')
	{
		if (data->args[0][j] == '/')
			return (1);
		j++;
	}
	while (env[i])
	{
		if (_strlen(env[i]) > 3)
			if (env[i][0] == 'P' && env[i][3] == 'H')
				break;
		i++;
	}
	path_env = env[i];
	pathdup = strdup(path_env);

	if (pathdup == NULL)
		return (0);
	if (parsePATH(pathdup, &pathtok))
		_concatPATH(pathtok, &path, cmd);
	else
	{
		free(pathdup);
		return (0);
	}
	i = 0;

	while (pathtok[i] != NULL)
		free(pathtok[i++]);
	free(pathtok[i]);
	free(pathtok);
	free(pathdup);
	free(data->args[0]);
	data->args[0] = path;

	return (1);
}

/**
 * parsePATH - function to parse the PATH variable into directories
 * Return: 1 if the parsing succeded and 0 otherwise
 * @path: the full PATH variable
 * @pathtok: the array of strings holding the directories
*/

int parsePATH(char *path, char ***pathtok)
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

	return (1);
}

/**
 * _concatPATH - function to find the directory of the command and concat it
 * Return: 1 if succeded and 0 otherwise
 * @pathtok: the array of strings holding the directories
 * @cmd: the command to find it's path
 * @concated: string holding the command concated to it's path
*/

int _concatPATH(char **pathtok, char **concated, char *cmd)
{
	char wd[256], cwd[256];
	int i = 0;
	struct stat buffer;

	if (pathtok == NULL)
		return (0);

	getcwd(cwd, 256);
	do {
		getcwd(wd, 256);
		if (!stat(cmd, &buffer))
			if (!_strcat(wd, cmd, concated))
			{
				perror("couldn't concat the strings");
				return (0);
			}

		chdir(pathtok[i]);
	} while (pathtok[++i] != NULL);
	chdir(cwd);
	return (1);
}
/**
 * _strcat - function to concat 2 strings with (/) between them
 * Return: 1 on if succeded and 0 otherwise
 * @s1: first string
 * @s2: second string
 * @concated: the string resulted after concating.
*/

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

	return (1);
}
