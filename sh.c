#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	char *params[] = {NULL, NULL};
	char *stat_buff = NULL;
	int status;
	struct stat ret;

	while (1)
	{
		printf("ʕ•ᴥ•ʔ ");
		getline(&input, &len, stdin);
		printf("len: %u\n", (unsigned int)len);
		input[len - 2] = '\0';
		params[0] = input;

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
