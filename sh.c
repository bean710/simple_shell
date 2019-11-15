#include "crikey.h"

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	char **params;
	char *stat_buff = NULL;
	int status;
	struct stat ret;

	token_t *n_params = NULL;
	token_t *tmp;
	int size, i;

	while (1)
	{
		n_params = NULL;

		printf("⚡ ");
		getline(&input, &len, stdin);
		dropnl(input);
		size = tokenize(&n_params, input);

		if (size == 0)
			continue;

		params = malloc(sizeof(char *) * (size + 1));

		for (i = 0, tmp = n_params; tmp; tmp = tmp->next, ++i)
			params[i] = tmp->str;

		params[i] = NULL;

		if (stat(params[0], &ret) != -1)
		{
			if (!fork())
				execve(params[0], params, NULL);
			else
				wait(&status);
		}
		else
			printf("Command not found: %s\n", params[0]);
	}

	free (input);
	return (0);
}

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

int tokenize(token_t **head, char *input)
{
	char *tmp = NULL;
	int len = 0;

	tmp = strtok(input, " ");

	while (tmp != NULL)
	{
		len++;
		append_token(head, tmp);
		tmp = strtok(NULL, " ");
	}

	return (len);
}
