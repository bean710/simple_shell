#include "crikey.h"

char *_strcat(char *dest, char *src)
{
	int countDestLen = 0;
	int i = 0;

	while (dest[countDestLen])
		countDestLen++;

	for (; src[i] != '\0'; i++)
	{
		dest[countDestLen + i] = src[i];
	}

	dest[countDestLen + i] = '\0';
	return (dest);
}


int _strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 != *s2)
			break;

		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

void translateExec(char **params, char **env)
{
	/*if (_strcmp(params[0], "ls") == 0)
		params[0] = "/bin/ls";*/
    unsigned int i, strLen = 0, x = 0, y = 0;
	char *pathStr, *tmp = NULL, char * path, *tmp2 = NULL;
	char *concatenatedString;

    i = 0;
    while (env[i] != NULL)
    {
        /*printf("%s\n", env[i]);*/
		pathStr = env[i];
		tmp = strtok(input, "=");

		while (tmp)
		{
			tmp = strtok(NULL, "=");
		}

		if (_strcmp(tmp[0] == "PATH") == 0)
		{
			path = tmp[1];
			tmp2 = strtok(path, ":");

			for (x = 0; tmp2[x] != '\0'; x++)
				;
			while (tmp2)
			{
				concatenatedString = malloc ((sizeof(char) * (x + y)) + 1);
				_strcat(concatenatedString, tmp2);
				_strcat(concatenatedString, params[0]);
				
				printf("\n%s\n", concatenatedString);
				free(concatenatedString);
				tmp2 = (NULL, ":");
			}
		}
        i++;
    }
    return (0);
}
