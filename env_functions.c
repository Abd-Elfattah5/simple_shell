#include "main.h"

void _unsetenv(shell_data *data)
{
	char ***envp = &data->_environ, **new_env = NULL, *name = NULL,
	     **av = data->args;
	int i, j;

	if (data->argc != 2)
	{
		printf("Error, invalid number of arguments\n");
		return;
	}
	name = av[1];
	for (i = 0; (*envp)[i] != NULL; ++i);
	printf("Before search\n");
	for (i = 0, j = 0; (*envp)[i] != NULL; ++i)
	{
		if (_strcmp2((*envp)[i], name) == 0
				&& ((*envp)[i])[_strlen(name)] == '=')
		{
			printf("Found %s\n", (*envp)[i]);
		}
		else
		{
			if (new_env == NULL)
				new_env = malloc(sizeof(char *) * 1);
			else
				new_env = realloc(new_env,
						sizeof(char *) * (j + 1));
			
			new_env[j++] = strdup((*envp)[i]);
		}
	}
	free_env(data);
	*envp = NULL;
	new_env = realloc(new_env, sizeof(char*) * (j + 1));
	new_env[j] = NULL;
	*envp = new_env;
	environ = *envp;
	printf("unset DONE\n");
	printf("after unset: %s\n", getenv(name));
}

void _setenv(shell_data *data)
{
	char **av = data->args, *new_var = NULL, ***envp = &data->_environ,
	     *name, *value;
	int i, overwrite = 1;

	if (data->argc != 3)
	{
		printf("Error, invalid number of arguments\n");
		return;
	}

	name = av[1];
	value = av[2];
	if (name == NULL || name[0] == '\0')
		return;

	new_var = _concat_all(name, value);
	if (new_var == NULL)
	{
		printf("Error, _concat_all failed\n");
		return;
	}
	printf("new_var: %s\n", new_var);
	for (i = 0; (*envp)[i] != NULL; ++i)
	{
		if (_strcmp2((*envp)[i], name) == 0
					&& ((*envp)[i])[_strlen(name)] == '=')
		{
			printf("Found %s\n", (*envp)[i]);
			if (!overwrite)
			{
				free(new_var);
				return;
			}
			free((*envp)[i]);
			(*envp)[i] = new_var;
			environ = *envp;
			new_var = NULL;
			printf("after edit: %s\n", (*envp)[i]);
			printf("getenv: %s\n", getenv(name));
			return;
		}
	}
	printf("NOT FOUND\n");
	for (i = 0; (*envp)[i] != NULL; ++i);
	*envp = (char **)realloc(*envp, sizeof(char *) * (i + 2));
	if (*envp == NULL)
	{
		printf("Error, malloc failed\n");
		return;
	}
	(*envp)[i++] = new_var;
	(*envp)[i] = NULL;
	environ = *envp;
	new_var = NULL;
	printf("after _setenv: %s=%s\n", name, getenv(name));
	return;
}
