#include "main.h"

/**
 * _getcmd - prompt the user for a command
 *
 * @data: shell_data
 * Return: (-1) on failure, else otherwise
 */
int _getcmd(shell_data *data)
{
	int _stat = 0;
	size_t n = 0;
	ssize_t nread;
	char **buf = &data->input;

	if (data->av[1] != NULL)
	{
		if (data->fd == NULL)
		{
			data->fd = fopen(data->av[1], "r");
			if (data->fd == NULL)
			{
				dprintf(STDERR_FILENO, "%s: 0: Can't open %s\n",
						data->av[0], data->av[1]);
				_perror(NULL, data, 127);
			}
		}
	}
	else
	{
		data->fd = stdin;
		_stat = isatty(STDIN_FILENO);
		if (_stat == 1)
			write(STDOUT_FILENO, "($) ", 4);
	}
	*buf = NULL;
	nread = getline(buf, &n, data->fd);
	if (nread == -1 && *buf)
	{
		free(*buf);
		*buf = NULL;
		_perror(NULL, data, data->status);
	}
	if (spaces_only(*buf))
	{
		free(*buf);
		return (0);
	}
	if (remove_comments(buf) == -1)
		return (0);
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
 * Return: void
 */
void _execve(shell_data *data)
{
	char **args = data->args;

	if (execve(args[0], args, NULL) == -1)
	{
		printf("%s: 1: %s: command not found\n",
				data->av[0], data->input);
		_perror("execve", data, EXIT_FAILURE);
	}
}

/**
 * spaces_only - check if the string is spaces only
 * @s: string to be checke
 * Return: (1) on if all spaces - (0) otherwise
 */
int spaces_only(char *s)
{
	int i;

	for (i = 0; s[i] != '\n'; ++i)
	{
		if (s[i] != ' ')
			return (0);
	}
	return (1);
}

/**
 * remove_comments - remove comments from the input
 * @s: string to remove comments from
 */
int remove_comments(char **s)
{
	int i = 0, to = 0;

	for (i = 0; (*s)[i] != '\0'; ++i)
	{
		if ((*s)[i] == '#')
		{
			if (i == 0)
			{
				free(*s);
				*s = NULL;
				return (-1);
			}
		if ((*s)[i - 1] == ' ' || (*s)[i - 1] == '\t' || (*s)[i - 1] == ';')
		{
			to = i;
		}
		}
	}
	if (to)
	{
		*s = realloc(*s, to + 1);
		(*s)[to] = '\0';
	}
	return (0);
}
