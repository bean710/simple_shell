#include "crikey.h"

/**
 * append_token - Appends a string to the end of a linked list
 * @head: Pointer to a pointer pointing to the first node in the linked list
 * @str: Pointer to the first character of the string that should be assigned
 * to the new node
 *
 * Return: Pointer to the newly added node
 */
token_t *append_token(token_t **head, char *str)
{
	token_t *node = malloc(sizeof(token_t));
	token_t *tmp = *head;

	if (node == NULL)
		return (NULL);

	node->str = str;
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

/**
 * tokenize - Tokenizes a string into a linked list
 * @head: Pointer to a pointer pointing to the first item in the linked list
 * of tokens
 * @input: The input string to be tokenized by the " " delimiter
 *
 * Return: Number of tokens tokenized
 */
int tokenize(token_t **head, char *input)
{
	char *tmp = NULL;
	int len = 0;

	tmp = _strtok(input, ' ');

	while (tmp != NULL)
	{
		len++;
		append_token(head, tmp);
		tmp = _strtok(NULL, ' ');
	}

	return (len);
}
