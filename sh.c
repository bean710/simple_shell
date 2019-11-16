#include "crikey.h"

int main(int argc, char **argv, char **env)
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
			print("\n");
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
		/*if (ustat(params[0], &ret) != -1)
		{
			if (!fork())
				execve(params[0], params, NULL);
			else
				wait(&status);
		}*/
		if (!translateExec(params, env))
			printf("Command not found: %s\n", params[0]);
		}
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
