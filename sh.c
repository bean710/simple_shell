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

	signal(SIGINT, SIG_IGN);

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
		input = _strtok(input, '#');
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
	int i;
	static int tally, exitStat;

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
		if (compareStat(params[0], &exitStat, params, n_params, tally) == 0)
			return;
		if (checkVanilla(params, &exitStat, n_params, tally, env) == 0)
			return;
	}
	free(params);
	freenodes(n_params);
}

/**
 * compareStat - compares the exitStat if 126 then frees the variables
 * @command: the first word the user inputs
 * @exitStat: the exit status of the program
 * @params: the double pointer where the tokenized inputs are stored
 * @n_params: the linked list
 * @tally: tally number
 *
 * Return: returns 0 if success, returns 1 if failed
 */
int compareStat(char *command, int *exitStat, char **params, token_t *n_params,
int tally)
{
	struct stat ret;

	if ((stat(command, &ret) == 0 && access(command, X_OK) != 0) || *exitStat
== 126)
	{
		*exitStat = 126;
		printComNotFound(tally, command);
		free(params);
		freenodes(n_params);
		return (0);
	}

	return (1);
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
