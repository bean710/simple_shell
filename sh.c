#include "crikey.h"

#define UNUSED __attribute__((unused))

/**
 * main - main function of a program
 * @UNUSED: Macro for unused parameters
 * @env: environment
 *
 * Return: none
 */
int main(int argc UNUSED, char **argv UNUSED, char **env)
{
	char *input = NULL;
	size_t len = 0;
	int is_term, size;
	token_t *n_params = NULL;

	is_term = isatty(STDIN_FILENO);

	while (1)
	{
		n_params = NULL;

		if (is_term)
			_print("⚡ ");
		if (getline(&input, &len, stdin) == -1)
		{
			free(input);
			if (is_term)
			{
				_print("\n");
				exit(70);
			}
			exit(0);
		}
		input = strtok(input, "#");
		dropnl(input);
		replaceTabs(input);
		size = tokenize(&n_params, input);
		helper(size, n_params, env, input);
	}
	free(input);
	return (0);
}

/**
 * helper - helper for main
 * @size: size
 * @n_params: node parameters
 * @env: contains the environment variables
 * @input: Contains the raw user input
 *
 * Return: no return
 */
void helper(int size, token_t *n_params, char **env, char *input)
{
	token_t *tmp;
	char **params;
	int i, status;
	static int tally = 0, exitStat;
	struct stat ret;

	tally++;

	if (size == 0)
		return;

	params = malloc(sizeof(char *) * (size + 1));

	for (i = 0, tmp = n_params; tmp; tmp = tmp->next, ++i)
		params[i] = tmp->str;
	params[i] = NULL;

	if (check_builtins(size, params, env, input, n_params, exitStat))
		return;

	if (!translateExec(params, env, &exitStat))
	{		

		if ((stat(params[0], &ret) == 0 && access(params[0], X_OK) != 0) ||
exitStat == 126)
		{
			exitStat = 126;
			printComNotFound(tally, params[0]);
			free(params);
			freenodes(n_params);
			return;
		}

		if (access(params[0], X_OK) == 0)
		{
			if (!fork())
					execve(params[0], params, NULL);	
			else
			{
				exitStat = 0;
				wait(&status);
				free(params);
				freenodes(n_params);
				return;
			}
		}
		else
		{
			exitStat = 127;
			printComNotFound(tally, params[0]);
		}
	}
	else
	{
		free(params);
		freenodes(n_params);
		return;
	}
}

/**
 * dropnl - Removes the newline from the end of a string
 * @src: Pointer to the string to manipulate
 */
void dropnl(char *src)
{
	int i;

	for (i = 0; src[i]; i++)
	{
		if (src[i] == '\n')
		{
			*(src + i) = '\0';
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
 * @n_params: Pointer to the linked list of parameter nodes
 * @input: Pointer to the raw user input
 *
 * Return: 1 if builtin found, 0 otherwise
 */
int check_builtins(int argnum, char **args, char **env, char *input, token_t
*n_params, int exitStat)
{
	size_t i;
	int exit_val;

	if (argnum == 0)
		return (0);

	if (_strcmp(args[0], "exit"))
	{
		if (argnum > 1)
		{
			exit_val = _atoi(args[1]);
			exit(exit_val);
		}
		freenodes(n_params);
		free(input);
		free(args);
		exit(exitStat);
	}
	else if (_strcmp(args[0], "env"))
	{
		for (i = 0; env[i]; ++i)
		{
			_print(env[i]);
			_print("\n");
		}
		freenodes(n_params);
		free(args);
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
