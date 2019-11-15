#include "crikey.h"

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	char **params;
	int status;
	struct stat ret;

	token_t *n_params = NULL;
	token_t *tmp;
	int size, i;

	while (1)
	{
		n_params = NULL;

		_print("⚡ ");
		if (getline(&input, &len, stdin) == -1)
		{
			_print("\n");
			exit(70);
		}

		dropnl(input);
		size = tokenize(&n_params, input);

		if (size == 0)
			continue;

		params = malloc(sizeof(char *) * (size + 1));

		for (i = 0, tmp = n_params; tmp; tmp = tmp->next, ++i)
			params[i] = tmp->str;

		params[i] = NULL;

		check_builtins(size, params);

		if (stat(params[0], &ret) != -1)
		{
			if (!fork())
				execve(params[0], params, NULL);
			else
				wait(&status);
		}
		else
			_print_s("Command not found: ", params[0]);
	}

	free (input);
	return (0);
}

/**
 * dropnl - Removes the newline from the end of a string
 * @src: Pointer to the string to manipulate
 */
void dropnl(char *src)
{
	for (; *src; src++)
	{
		if (*src == '\n')
		{
			*src = '\0';
			return;
		}
	}
}

/**
 * check_builtins - checks for builtin functions and runs
 * @argnum: Number of arguments
 * @args: Pointer to the first pointer in an array of pointers each pointing
 * to a string
 *
 * Return: 1 if builtin found, 0 otherwise
 */
int check_builtins(int argnum, char **args)
{
	if (argnum == 0)
		return (0);

	if (_strcmp(args[0], "exit"))
		exit (0);

	return (0);
}
