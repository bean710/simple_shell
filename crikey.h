#ifndef _CRIKEY_
#define _CRIKEY_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

typedef struct token_s
{
	char* str;
	struct token_s *next;
} token_t;

void dropnl(char *src);
token_t *append_token(token_t **head, const char *str);
char *_strdup(const char *src);
int _strcmp(char *s1, char *s2);
int translateExec(char **params, char **env);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

#endif
