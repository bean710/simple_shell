#include "crikey.h"

int _getline(char **o_buff)
{
	char *buffer = malloc(sizeof(char) * (128 + 1));
	size_t b_size = 128, index;
	char c;

	if (!buffer)
		return (-1);

	c = _getchar(-1);
	if (c == EOF)
	{
		if (*o_buff != NULL)
			free(*o_buff);
		*o_buff = buffer;
		
		return (-1);
	}

	while (c != EOF && c == ' ')
		c = _getchar(1);

	index = 0;
	while (c != EOF && c != '\n')
	{
		if (index % 128 == 0 && index != 0)
		{
			buffer = _realloc(buffer, b_size, b_size + 128);
			b_size += 128;
		}

		buffer[index] = c;
		c = _getchar(0);
		index++;
	}

	buffer[index] = '\0';

	if (*o_buff != NULL)
		free(*o_buff);

	*o_buff = buffer;

	if (c == EOF)
		return (-1);

	return (index);
}

/**
 * _realloc - Allocates space of `new_size` bytes and moves old data to new
 *            space.
 * @ptr: Pointer to the old memory space
 * @old_size: The size in bytes of the old memory space
 * @new_size: The size in bytes of the new memory space
 *
 * Return: Pointer to the new memory space
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new = malloc(new_size);

	if (new == NULL)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		*((unsigned char *)new + i) = *((unsigned char *)ptr + i);

	free(ptr);
	return (new);
}
