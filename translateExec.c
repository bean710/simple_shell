#include "crikey.h"

/**
 * _strcat - concatenates a string
 * @dest: the string to be concatenated
 * @src: the string to add to dest
 *
 * Return: returns char string array
 */
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


/**
 * _strcpy - copies the string pointed to by src
 * @dest: pointer
 * @src: pointer
 *
 * Return: returns char string array
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

/**
 * translateExec - executes the file to a string
 * @params: contains the parameters from the user input
 * @env: contains the environment variables
 *
 * Return: returns char string array
 */
int translateExec(char **params, char **env)
{
	int i = 0, pathLen = 0, paramLen = 0, tokLen = 0;
	char *path, *enVariable;
	char *param = params[0];

	/*gets Parameter[0] length*/
	for (paramLen = 0; param[paramLen]; paramLen++)
		;

	/*loop through each instance variable in environment*/
	while (env[i])
	{
		enVariable = env[i];

		for (pathLen = 0; enVariable[pathLen]; pathLen++)
			;

		path = malloc(sizeof(char) * pathLen + 1);
		if (path == NULL)
			exit(1);
		_strcpy(path, enVariable);

		/*check for PATH environment variable*/
		enVariable = strtok(path, "=");
		checkEnvVariable(enVariable, tokLen, paramLen, param, params);

		i++;
		free(path);
	}
	return (1);
}

/**
 * checkEnvVariable - a helper function to execute files if equals "PATH"
 * @enVariable: environment variable
 * @tokLen: token length, int
 * @paramLen: param length, int
 * @param: param, the first value of params
 * @params a double pointer that points to params
 *
 * Return: no return
 */
void checkEnvVariable(char *enVariable, int tokLen, int paramLen, char *param,
char **params)
{
	char *testExec, *enValue, *enVariableToken;
	int status, j = 0;

	if (_strcmp(enVariable, "PATH") == 1)
	{
		enValue = strtok(NULL, "=");
		enVariableToken = strtok(enValue, ":");

		while (enVariableToken)
		{
			for (tokLen = 0; enVariableToken[tokLen]; tokLen++)
				;
			testExec = malloc(sizeof(char) * (paramLen + tokLen + 2));
			for (j = 0; j < paramLen + tokLen + 2; ++j)
				testExec[j] = '\0';

			if (testExec == NULL)
				exit(1);
			_strcat(testExec, enVariableToken);
			_strcat(testExec, "/");
			_strcat(testExec, param);
			_strcat(testExec, "\0");

			if (access(testExec, X_OK) == 0)
			{
				if (!fork())
					execve(testExec, params, NULL);
				else
					wait(&status);
			}
				enVariableToken = strtok(NULL, ":");
				free(testExec);
		}
	}
}

