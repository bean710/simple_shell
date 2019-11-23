#include "crikey.h"

/**
 * id_print - prints percent i and percent d
 * @n: the integer to print
 *
 *
 * Return: integer
 */
void id_print(int n)
{
	unsigned int m;

	if (n < 0)
	{
		_putchar('-');
		m = -n;
	}
	else
		m = n;
	if (m / 10)
	{
		id_print(m / 10);
	}
	_putchar(m % 10 + '0');
}

/**
 * printExitStatus - prints the exit status to the user
 * @tally: the tally number
 * @exitStatus: exit status of the child
 *
 * Return: no return
 */
void printExitStatus(int tally, int exitStatus)
{
	_print("sh: ");
	id_print(tally);
	_print(": ");
	id_print(exitStatus);
	_print(": not found\n");
}

/**
 * printComNotFound - prints the exit status to the user
 * @tally: the tally number
 * @exitStatus: exit status of the child
 *
 * Return: no return
 */
void printComNotFound(int tally, char *command)
{
	_print("sh: ");
	id_print(tally);
	_print(": ");
	_print(command);
	_print(": not found\n");
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1)); /* writes to stdio */
}


