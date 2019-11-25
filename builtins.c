#include "crikey.h"

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
	if (argnum == 0)
		return (0);

	if (_strcmp(args[0], "exit"))
		biexit(n_params, input, args, argnum, exitStat);
	else if (_strcmp(args[0], "env"))
	{
		bienv(env, n_params, args);
		return (1);
	}
	else if (_strcmp(args[0], "help"))
	{
		bihelp(args, n_params);
		return (1);
	}

	return (0);
}

/**
 * bihelp - Prints help messages for builtins
 * @args: Pointer to the first pointer in an array of pointers, each pointing
 * to an argument
 * @n_params: Linked list of the parameters
 */
void bihelp(char **args, token_t *n_params)
{
	if (_strcmp(args[1], "exit"))
	{
		_print("Usage: exit [status]\n");
		_print("Exits with a certain status (or 0 if no status given)\n");
	}
	else if (_strcmp(args[1], "env"))
		_print("Usage: env\nPrints the the current environment\n");
	else if (_strcmp(args[1], "help"))
		_print("Usage: help (builtin)\nShows how to use the given builtin\n");
	else
		_print_s("Error: no builtin: ", args[1]);

	freenodes(n_params);
	free(args);
}

/**
 * biexit - Runs the exit builtin
 * @n_params: Linked list of the parameters
 * @input: Pointer to the raw input
 * @args: Pointer to the arguments
 * @argnum: Number of arguments
 * @exitStatus: Status to exit with if no other status is specified
 */
void biexit(token_t *n_params, char *input, char **args, int argnum,
		int exitStat)
{
	int exit_val;

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

/**
 * bienv - Runs the env builtin
 * @env: Pointer to the env varable
 * @n_params: Linked list of the parameters
 * @args: Pointer to the arguments
 */
void bienv(char **env, token_t *n_params, char **args)
{
	int i;

	for (i = 0; env[i]; ++i)
	{
		_print(env[i]);
		_print("\n");
	}
	freenodes(n_params);
	free(args);
}
