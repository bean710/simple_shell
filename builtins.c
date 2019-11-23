#include "crikey.h"

void biexit(token_t *n_params, char *input, char **args, int argnum)
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
	exit(0);
}

