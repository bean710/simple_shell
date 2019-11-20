#include "crikey.h"

/**
 * main - main function of a program
 * @argc: argument count
 * @argv: argument vector
 * @env: environment
 *
 * Return: none
 */
int main(int argc __attribute__((unused)), char **argv __attribute__((unused))
, char **env)
{
	char *input = NULL, **params = NULL;
	size_t len = 0;
	int is_term, size, ret_val_helper = 0;
	token_t *n_params = NULL;

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
		ret_val_helper = helper(size, params, n_params, env);
		if (ret_val_helper == 1)
		{
			ret_val_helper = 0;
			continue;
		}
		free(params);
		freenodes(n_params);
	}
	free(input);
	return (0);
}

/**
 * helper - helper for main
 * @size: size
 * @params: parameters
 * @n_params: node parameters
 * @env: contains the environment variables
 *
 * Return: integer value, to determine the to 1 continue or 0 not
 */
int helper(int size, char **params, token_t *n_params, char **env)
{
	token_t *tmp;
	int i, status;

	if (size == 0)
		return (1);

	params = malloc(sizeof(char *) * (size + 1));

	for (i = 0, tmp = n_params; tmp; tmp = tmp->next, ++i)
		params[i] = tmp->str;

	params[i] = NULL;
	if (check_builtins(size, params, env))
	{
		free(params);
		freenodes(n_params);
		return (1);
	}

	if (!translateExec(params, env))
	{
		if (access(params[0], X_OK) == 0)
		{
			if (!fork())
				execve(params[0], params, NULL);
			else
				wait(&status);
		}
		else
			printf("Command not found: %s\n", params[0]);
	}

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
 * @env: environment variable
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
		exit(0);
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

/**
 * freenodes - frees the nodes to avoid memory leaks
 * @head: points to the first node of a linked list
 *
 * Return: none
 */
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
