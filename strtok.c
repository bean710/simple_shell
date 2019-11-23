#include "crikey.h"

/**
 * _strtok - Tokenizes a string by a character delimiter
 * @src: The string to be tokenized on the first call, should be NULL for
 * subsequent calls when tokenizing the same string
 * @delim: The delimiter to tokenize by
 *
 * Return: Pointer to the beginning of the new token
 */
char *_strtok(char *src, char delim)
{
	static char *start;
	static char *last_null;
	char *ret = NULL;

	if (src)
		start = src;

	if (!start)
		return (NULL);

	if (*start == '\0')
	{
		if (start == last_null)
		{
			start = NULL;
			return (NULL);
		}
		last_null = start;
		return (start);
	}

	ret = start;
	while (*start)
	{
		if (*start == delim)
		{
			*start = '\0';
			last_null = start;
			start++;
			return (ret);
		}
		start++;
	}
	last_null = start;

	return (ret);
}
