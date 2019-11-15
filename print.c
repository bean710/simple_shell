#include "crikey.h"

/**
 * _print - prints a string
 * @src: The string to be printed
 *
 * Return: Number of characters printed
 */
int _print(char *src)
{
	size_t len;
	int ret;
	
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
	size_t len, tot = 0;
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
