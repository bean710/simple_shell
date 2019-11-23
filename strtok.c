#include "crikey.h"

char *_strtok(char *src, char delim)
{
	static char *start = NULL;
	static char *last_null = NULL;
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
