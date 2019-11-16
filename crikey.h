#ifndef _CRIKEY_
#define _CRIKEY_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

typedef struct token_s
{
	char* str;
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
int _strcmp(char *s1, char *s2);
int check_builtins(int argnum, char **args, char **env);
int _atoi(char *s);
void freenodes(token_t *head);

#endif
