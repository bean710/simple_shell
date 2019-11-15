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
token_t *append_token(token_t **head, char *str);
char *_strdup(const char *src);
int tokenize(token_t **head, char *input);
int _print(char *src);

#endif
