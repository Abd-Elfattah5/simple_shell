#include "main.h"
/**
 * _cd - function to implement the cd builtin
 * Return: none
 * @data: the data needed
*/
void _cd(shell_data *data)
{
	if (data->args[1] == NULL)
	{
		cd_no_arg(data);
	}
	else if (!_strcmp(data->args[1], "-"))
	{
		cd_hiffen(data);
	}
	else
	{
		cd_arg(data);
	}
}

/**
 * cd_no_arg - function to return to the home directory
 * Return: none
 * @data: the data needed
*/

void cd_no_arg(shell_data *data)
{
	char **env = data->_environ, *token;
	int i = 0;

	while (env[i])
	{
		if (_strlen(env[i]) > 3)
			if (env[i][0] == 'H' && env[i][3] == 'E')
				break;
		i++;
	}
	token = strtok(env[i], "=");
	token = strtok(NULL, "=");

	getcwd(data->prev_wd, 1024);
	chdir(token);
}

/**
 * cd_hiffen - function to return to the previous directory
 * Return: none
 * @data: the data needed
*/

void cd_hiffen(shell_data *data)
{
	char *token;

	token = strdup(data->prev_wd);

	if (token == NULL)
	{
		perror("strdup");
		return;
	}
	getcwd(data->prev_wd, 1024);
	chdir(token);
	free(token);
}

/**
 * cd_arg - function to implement the cd builtin with arguments
 * Return: none
 * @data: the data needed
*/

void cd_arg(shell_data *data)
{
	char *token;
	int i;

	token = strdup(data->prev_wd);

	if (token == NULL)
	{
		perror("strdup");
		return;
	}
	getcwd(data->prev_wd, 1024);
	if (chdir(data->args[1]) == -1)
	{
		dprintf(STDERR_FILENO, "%s: 1: cd: can't cd to %s\n",
				data->args[0], data->args[1]);
		for (i = 0; token[i] != '\0'; i++)
			(data->prev_wd)[i] = token[i];
		free(token);
		return;
	}
	free(token);
}
