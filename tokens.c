#include "crikey.h"

token_t *append_token(token_t **head, const char *str)
{
	token_t *node = malloc(sizeof(token_t));
	token_t *tmp = *head;

	if (node == NULL)
		return (NULL);

	if (str == NULL)
		node->str = NULL;
	else
	{
		node->str = _strdup(str);
		if (!node->str)
		{
			free(node);
			return (NULL);
		}
	}
	node->next = NULL;

	if (*head != NULL)
	{
		for (tmp = *head; tmp->next != NULL; tmp = tmp->next)
			;
		tmp->next = node;
	}
	else
		*head = node;

	return (node);
}

char *_strdup(const char *src)
{
	size_t len, i;
	char *ret;

	for (len = 0; src[len]; len++)
		;

	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);

	for (i = 0; src[i]; i++)
		ret[i] = src[i];

	ret[i] = '\0';

	return (ret);
}
