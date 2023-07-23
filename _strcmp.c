#include "main.h"
/**
 * _strcmp - function that compares two strings.
 *
 * @s1: first string
 * @s2: second string
 * Return: (0) on success - (-1) on failure
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	if (s1 && s2)
	{
		if (_strlen(s1) == _strlen(s2))
		{
			while (i < _strlen(s1))
			{
				if (s1[i] != s2[i])
					return (-1);
				i++;
			}
			return (0);
		}
	}
	return (-1);
}

