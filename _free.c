#include "main.h"

/**
 * free_in_buffers - free the input buffers
 * @data: shell_data
 */
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

/**
 * free_env - free environ variable
 * @data: shell_data
 */
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

/**
 * free_shell_data - free all shell data
 * @data: shell_data
 */
void free_shell_data(shell_data *data)
{
	free_in_buffers(data);
	free_env(data);
	if (data->fd != NULL && data->fd != stdin)
		fclose(data->fd);
}

