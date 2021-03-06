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
int translateExec(char **params, char **env, int *exitStatus);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int tokenize(token_t **head, char *input);
int _print(char *src);
int _print_s(char *src, char *end);
int check_builtins(int argnum, char **args, char **env, char *input, token_t
*n_params, int exitStat);
int _atoi(char *s);
void freenodes(token_t *head);
int checkEnvVariable(char *enVariable, int tokLen, int paramLen, char *param,
char **params, char *path, char *cwd, int *exitStatus, char **env);
void helper(int size, token_t *n_params, char **env, char *input);
void biexit(token_t *n_params, char *input, char **args, int argnum, int);
void replaceTabs(char *src);
void id_print(int n);
void printExitStatus(int tally, int exitStatus);
void printComNotFound(int tally, char *command);
int _putchar(char c);
char *_strtok(char *src, char delim);
char *getEnvVal(char **env, char *match);
void bienv(char **env, token_t *n_params, char **args);
void bihelp(char **args, token_t *n_params);
void concatTok(char *testExec, char *param, char *enVarToken);
int compareStat(char *command, int *exitStat, char **params, token_t *n_params,
int tally);
int checkVanilla(char **params, int *exitStat, token_t *n_params, int tally,
		char **env);

#endif
