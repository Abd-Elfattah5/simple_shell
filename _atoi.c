#include "main.h"
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

