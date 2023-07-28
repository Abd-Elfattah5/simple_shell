#include "main.h"

/**
 * is_full_path - check if the command with full path
 * @s: command
 * Return: (1) if full path - (0) if not
 */
int is_full_path(char *s)
{
	int j = 0;

	while (s[j] != '\0')
	{
		if (s[j] == '/')
			return (1);
		j++;
	}
	return (0);
}

/**
 * found_path - found the path env
 * @env; env var
 * Return: (-1) on failure - else otherwise
 */
int found_path(char **env)
{
	char *token = NULL;
	int i = 0;

	while(env[i] != NULL)
	{
		token = strtok(env[i], "=");
		token = strtok(NULL, "=");
		if (_strcmp(token, "PATH") == 0)
			return (i);
		token = NULL;
		i++;
	}
	return (-1);
}
