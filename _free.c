#include "main.h"

void free_in_buffers(shell_data *data)
{
	char **input = &data->input, ***args = &data->args;
	int i;

	if (*input)
		free(*input);
	*input = NULL;
	if (*args)
	{
		for (i = 0; (*args)[i] != NULL; ++i)
		{
			free((*args)[i]);
			(*args)[i] = NULL;
		}
		free(*args);
		*args = NULL;
	}
}

void free_env(shell_data *data)
{
	char ***env = &data->_environ;
	int i;

	if (*env)
	{
		for (i = 0; (*env)[i] != NULL; ++i)
		{
			free((*env)[i]);
			(*env)[i] = NULL;
		}
		free(*env);
		*env = NULL;
	}
}

void free_shell_data(shell_data *data)
{
	free_in_buffers(data);
	free_env(data);
}
