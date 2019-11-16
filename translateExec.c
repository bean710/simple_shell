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


/**
 * _strcpy - copies the string pointed to by src
 * @dest: pointer
 * @src: pointer
 *
 * Return: returns char string array
 *
 */
char *_strcpy(char *dest, char *src)
{
	int counter = 0;

	while (src[counter])
	{
		dest[counter] = src[counter];
		counter++;
	}

	dest[counter] = '\0';
	return (dest);
}


int translateExec(char **params, char **env)
{
	int i = 0, pathLen = 0, paramLen = 0, tokLen = 0, status;
	char *path, *enValue, *enVariable, *enVariableToken, *testExec;
	char *param = params[0];
	struct stat ret;

	/*gets Parameter[0] length*/
	for (paramLen = 0; param[paramLen]; paramLen++)
		;

	/*loop through each instance variable in environment*/
	while (env[i])
	{
		char *enVariable = env[i];

		for (pathLen = 0; enVariable[pathLen]; pathLen++)
			;

		path = malloc(sizeof(char) * pathLen + 1);
		if (path == NULL)
			exit(1);
		_strcpy(path, enVariable);

		/*check for PATH environment variable*/
		enVariable = strtok(path, "=");
		if(_strcmp(enVariable, "PATH") == 0)
		{
			enValue = strtok(NULL, "=");
			enVariableToken = strtok(enValue, ":");

			while (enVariableToken)
			{
				for (tokLen = 0; enVariableToken[tokLen]; tokLen++)
					;
				testExec = malloc((sizeof(char) * (paramLen + tokLen)) + 2);
				if(testExec == NULL)
					exit(1);
				_strcat(testExec, enVariableToken);
				_strcat(testExec, "/");
				_strcat(testExec, param);
				_strcat(testExec, "\0");
				/*if (ustat(testExec, &ret) != -1)
				{
					if (!fork())
						execve(testExec, params, NULL);
					else
						wait(&status);
				}*/
				printf("%s\n", testExec);
				enVariableToken = strtok(NULL, ":");
				free(testExec);
			}
		}
		i++;
		free(path);
	}
	return (1);
}
