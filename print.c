#include "crikey.h"

/**
 * _print - prints a string
 * @src: The string to be printed
 *
 * Return: Number of characters printed
 */
int _print(char *src)
{
	int len, ret;

	for (len = 0; src[len]; ++len)
		;

	ret = write(STDOUT_FILENO, src, len);

	if (ret != len)
	{
		write(STDERR_FILENO, "Error writing\n", 14);
		exit(71);
	}

	return (ret);
}

int _print_s(char *src, char *end)
{
	int len, tot = 0;
	int ret;

	for (len = 0; src[len]; ++len)
		;
	tot += len;

	ret = write(STDOUT_FILENO, src, len);

	for (len = 0; end[len]; ++len)
		;
	tot += len;

	ret += write(STDOUT_FILENO, end, len);

	ret += write(STDOUT_FILENO, "\n", 1);
	tot += 1;

	if (ret != tot)
	{
		write(STDERR_FILENO, "Error writing\n", 14);
		exit(71);
	}

	return (ret);
}

/**
 * strcmp - compares two strings
 * @s1: First string
 * @s2: Second string
 *
 * Return: 1 for match, 0 for not a match
 */
int _strcmp(char *s1, char *s2)
{
	for (; *s1 && *s2; ++s1, ++s2)
	{
		if (*s1 != *s2)
			return (0);
	}
	if (*s1 != *s2)
		return (0);

	return (1);
}

/**
 * _atoi - Converts a string to an integer
 * @s: pointer to the first character of the string
 *
 * Return: Value of integer in string
 */
int _atoi(char *s)
{
	unsigned int num;
	int neg;

	neg = 1;
	num = 0;

	for (; *s; s++)
	{
		if (*s >= '0' && *s <= '9')
		{
			num *= 10;
			num += *s - '0';
		}
		else if (num > 0)
		{
			break;
		}
		else if (*s == '-')
		{
			neg = -neg;
		}
	}

	return (num * neg);
}
