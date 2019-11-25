#include "crikey.h"

/**
 * checkVanilla - runs the command if the user inputs a directory
 * @params: the double pointer where the tokenized inputs are stored
 * @exitStat: the exit status of the program
 * @n_params: the linked list
 * @tally: tally number
 *
 * Return: returns 0 if success, returns 1 if failed
 */
int checkVanilla(char **params, int *exitStat, token_t *n_params, int tally,
		char **env)
{
	int status;

	if (access(params[0], X_OK) == 0)
	{
		if (!fork())
			execve(params[0], params, env);
		else
		{
			*exitStat = 0;
			wait(&status);
			free(params);
			freenodes(n_params);
			return (0);
		}
	}
	else
	{
		*exitStat = 127;
		printComNotFound(tally, params[0]);
	}

	return (1);
}
