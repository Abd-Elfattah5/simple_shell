#include "main.h"

/**
 * is_full_path - check if the command with full path
 * @s: command
 * Return: (1) if full path - (0) if not
 */
int is_full_path(char *s)
{
	while (s[j] != '\0')
	{
		if (s[j] == '/')
			return (1);
		j++;
	}
	return (0);
}
