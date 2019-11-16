#include "crikey.h"

int main(int argc, char **argv, char **env)
{
	char *input = NULL;
	size_t len = 0;
	char **params;
	int status, is_term;
	struct stat ret;

	token_t *n_params = NULL;
	token_t *tmp;
	int size, i;

	(void)argc;
	(void)argv;

	is_term = isatty(STDIN_FILENO);

	while (1)
	{		
		n_params = NULL;

		if (is_term)
			_print("⚡ ");

		if (getline(&input, &len, stdin) == -1)
		{
			free(params);
			free(input);
			freenodes(n_params);
			if (is_term)
			{
				_print("\n");
				exit(70);
			}
			exit(0);
		}

		dropnl(input);
		size = tokenize(&n_params, input);

		if (size == 0)
			continue;

		params = malloc(sizeof(char *) * (size + 1));

		for (i = 0, tmp = n_params; tmp; tmp = tmp->next, ++i)
			params[i] = tmp->str;

		params[i] = NULL;

		if (check_builtins(size, params, env))
			continue;

		if (stat(params[0], &ret) != -1)
		{
			if (!fork())
				execve(params[0], params, NULL);
			else
				wait(&status);
		}
		else
			_print_s("Command not found: ", params[0]);

		free(params);
		freenodes(n_params);
	}

	free(input);
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
int check_builtins(int argnum, char **args, char **env)
{
	size_t i;
	int exit_val;

	if (argnum == 0)
		return (0);

	if (_strcmp(args[0], "exit"))
	{
		if (argnum > 1)
		{
			exit_val = atoi(args[1]);
			exit(exit_val);
		}
		exit (0);
	}
	else if (_strcmp(args[0], "env"))
	{
		for (i = 0; env[i]; ++i)
		{
			_print(env[i]);
			_print("\n");
		}
		return (1);
	}

	return (0);
}

void freenodes(token_t *head)
{
	token_t *next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}
