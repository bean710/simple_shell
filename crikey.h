#ifndef _CRIKEY_
#define _CRIKEY_

typedef struct token_s
{
	char* chunk;
	struct token_s *next;
} token_t;

void dropnl(char *src);

#endif
