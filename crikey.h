#ifndef _CRIKEY_
#define _CRIKEY_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

/**
 * struct token_s - Structure that is a node, it handles the tokenized input
 * from the user in shell
 * @str: contains a pointer to a string that are tokens
 * @next: a member that points to another node that is also a struct token_s
 */
typedef struct token_s
{
	char *str;
	struct token_s *next;
} token_t;

void dropnl(char *src);
token_t *append_token(token_t **head, char *str);
int _strcmp(char *s1, char *s2);
int translateExec(char **params, char **env);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int tokenize(token_t **head, char *input);
int _print(char *src);
int _print_s(char *src, char *end);
int check_builtins(int argnum, char **args, char **env);
int _atoi(char *s);
void freenodes(token_t *head);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char _getchar(void);
int _getline(char **o_buff);

#endif
