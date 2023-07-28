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
 * @env: env var
 * Return: (-1) on failure - else otherwise
 */
int found_path(char **env)
{
	char *token = NULL, *str = NULL;
	int i = 0;

	while (env[i] != NULL)
	{
		str = strdup(env[i]);
		if (str == NULL)
			return (-1);

		token = strtok(str, "=");
		if (_strcmp(token, "PATH") == 0)
		{
			free(str);
			token = NULL;
			str = NULL;
			return (i);
		}
		free(str);
		token = NULL;
		str = NULL;
		i++;
	}
	return (-1);
}

