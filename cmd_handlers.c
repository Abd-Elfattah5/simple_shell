#include "main.h"

/**
 * _getcmd - prompt the user for a command
 *
 * @buf: buffer to store the command line
 * Return: (-1) on failure, else otherwise
 */
int _getcmd(char **buf)
{
	int _stat = 0;
	size_t n = 0;
	ssize_t nread;

	_stat = isatty(STDIN_FILENO);
	if (_stat == 1)
		write(STDOUT_FILENO, "($) ", 4);

	*buf = NULL;
	nread = getline(buf, &n, stdin);
	if (nread == -1 && *buf)
	{
		free(*buf);
		*buf = NULL;
		return (-1);
	}
	if (_strlen(*buf) <= 1)
	{
		free(*buf);
		*buf = NULL;
		return (0);
	}
	return (nread);
}

/**
 * _parsecmd - parse the command into tokens (arguments)
 *
 * @data: shell_data
 * Return: (-1) on failure, (0) on success
 */
int _parsecmd(shell_data *data)
{
	char *token = NULL, *cmd_cpy = NULL, *delim = " \n",
	     *cmd = data->input, ***argv = &data->args;
	int argc = 1, i = 0;

	cmd_cpy = strdup(cmd);
	if (cmd_cpy == NULL)
	{
		printf("Error, strdup failed\n");
		return (-1);
	}
	token = strtok(cmd, delim);
	while (token)
	{
		token = strtok(NULL, delim);
		argc++;
	}
	data->argc = argc - 1;
	*argv = (char **)malloc(sizeof(char *) * argc);
	if (*argv == NULL)
	{
		printf("Error, malloc failed\n");
		free(cmd_cpy);
		return (-1);
	}
	token = strtok(cmd_cpy, delim);
	for (i = 0; token != NULL; ++i)
	{
		(*argv)[i] = strdup(token);
		if ((*argv)[i] == NULL)
		{
			printf("Error, strdup2 failed\n");
			free_in_buffers(data);
			free(cmd_cpy);
			return (-1);
		}
		token = strtok(NULL, delim);
	}
	(*argv)[i] = NULL;
	free(cmd_cpy);
	return (0);
}

/**
 * _execve - execute the command
 *
 * @data: shell_data
 * Return: (-1) on failure, else otherwise
 */
int _execve(shell_data *data)
{
	char **args = data->args;

	if (execve(args[0], args, NULL) == -1)
	{

		printf("%s: 1: %s: command not found\n",
				data->av[0], data->input);
		printf("Error, execve failed\n");
		return (-1);
	}
	return (0);
}

