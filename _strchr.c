#include "main.h"

/**
 * _strchr - locate character in string
 *
 * @s: string
 * @c: char
 * Return: char*
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	if (s == NULL)
		return (NULL);

	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

