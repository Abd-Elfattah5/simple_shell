#include "main.h"

/**
 * _strcmp - function that compares two strings.
 *
 * @s1: first string
 * @s2: second string
 * Return: (0) on success - (-1) on failure
 */
int _strcmp(const char *s1, const char *s2)
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

/**
 * _strcmp2 - function that compares two strings till the min length.
 *
 * @s1: first string
 * @s2: second string
 * Return: int
 */
int _strcmp2(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] == s2[i])
	{
		if (s1[i + 1] == '\0' || s2[i + 1] == '\0')
			return (0);
		i++;
	}
	return (-1);
}

/**
 * _strlen - function that returns the length of a string.
 *
 * @s: string to return it's length
 * Return: The length of the string (int)
 */
int _strlen(const char *s)
{
	int len = 0;

	if (s)
	{
		while (s[len] != '\0')
			len++;
	}
	return (len);
}

/**
 * _atoi - function that convert a string to an integer.
 *
 * @s: string to be converted
 *
 * Return: string after converting (int)
 */
int _atoi(char *s)
{
	int sign = 1, j, i;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
			break;
	}
	j = i;
	while (s[j] >= '0' && s[j] <= '9')
	{
		res = (res * 10) + (s[j] - '0');
		j++;
	}
	res *= sign;
	return (res);
}

/**
 * _concat_all - function the concatinates tow string with a separetor
 *
 * @s1: first string
 * @s2: second string
 * Return: (char*) concatenated string
 */
char *_concat_all(const char *s1, const char *s2)
{
	char *res;
	int l1, l3, i, j;

	l1 = _strlen(s1);
	l3 = _strlen(s2);
	res = malloc(l1 + l3 + 2);
	if (res == NULL)
		return (NULL);
	for (i = 0; s1[i] != '\0'; ++i)
		res[i] = s1[i];
	res[i++] = '=';
	for (j = 0; s2[j] != '\0'; ++j)
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}

