#include "main.h"

/**
 * is_found - check if the current variable name = name
 * @envp: environ
 * @name: variable name
 * @new_var: new variabel
 * @overwrite: overwrite flag
 * Return: (1) on success, (0) on failure
 */
int is_found(char ***envp, char *name, char **new_var, int overwrite, int i)
{
	if (_strcmp2((*envp)[i], name) == 0 &&
			((*envp)[i])[_strlen(name)] == '=')
	{
		if (!overwrite)
		{
			free(*new_var);
			return (1);
		}
		free((*envp)[i]);
		(*envp)[i] = *new_var;
		environ = *envp;
		*new_var = NULL;
		return (1);
	}
	return (0);
}

/**
 * _unsetenv - unset variable in environ
 *
 * @data: shell_data
 */
void _unsetenv(shell_data *data)
{
	char ***envp = &data->_environ, **new_env = NULL, *name = NULL,
	     **av = data->args;
	int i, j;

	if (data->argc != 2)
	{
		perror("Error, invalid number of arguments");
		return;
	}
	name = av[1];
	for (i = 0; (*envp)[i] != NULL; ++i)
		;
	for (i = 0, j = 0; (*envp)[i] != NULL; ++i)
	{
		if (_strcmp2((*envp)[i], name) == 0 &&
				((*envp)[i])[_strlen(name)] == '=')
		{
			continue;
		}
		else
		{
			if (new_env == NULL)
				new_env = malloc(sizeof(char *) * 1);
			else
				new_env = realloc(new_env,
						  sizeof(char *) * (j + 1));
			if (new_env == NULL)
				perror("Error allocating memory");
			new_env[j++] = strdup((*envp)[i]);
		}
	}
	free_env(data);
	*envp = NULL;
	new_env = realloc(new_env, sizeof(char *) * (j + 1));
	new_env[j] = NULL;
	*envp = new_env;
	environ = *envp;
}

/**
 * _setenv - set variable in environ
 *
 * @data: shell_data
 */
void _setenv(shell_data *data)
{
	char **av = data->args, *new_var = NULL, ***envp = &data->_environ,
	     *name, *value;
	int i, overwrite = 1;

	if (data->argc != 3)
	{
		perror("Error, invalid number of arguments");
		return;
	}
	name = av[1];
	value = av[2];
	new_var = _concat_all(name, value);
	if (new_var == NULL)
	{
		perror("Error _concat_all failed");
		return;
	}
	for (i = 0; (*envp)[i] != NULL; ++i)
	{
		if (is_found(envp, name, &new_var, overwrite, i))
			return;
	}
	for (i = 0; (*envp)[i] != NULL; ++i)
		;
	*envp = (char **)realloc(*envp, sizeof(char *) * (i + 2));
	if (*envp == NULL)
	{
		perror("Error allocating memory");
		return;
	}
	(*envp)[i++] = new_var;
	(*envp)[i] = NULL;
	environ = *envp;
	new_var = NULL;
}

