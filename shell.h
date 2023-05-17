#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BLT_IN_RET "builtin"

/**
 * struct typ - Struct typ
 *
 * @name: Built in command name
 * @f: Built in command function
 */
typedef struct typ
{
	char *name;
	void (*f)(char **argv);
} built_in_t;

/**
 * struct env_typ - Struct env_typ
 *
 * @val: Env value
 * @idx: Env index
 * @len: Size of env array
 */
typedef struct env_typ
{
	char *val;
	int idx;
	int len;
} env_typ_t;

extern char **environ;
void _putchar(char c, int fd);
void _putstr(char *s, int fd);
unsigned int _strlen(char *s);
void _strcpy(char *src, char *sink);
void _strcpy_n_o(char *src, char *sink);
char **extract_term_args(char *stdin_bfr);
int _strincludes(char *s, char c);
char *_pathconcat(char *first, char link, char *second);
char *handle_path(char *bfr);
char *_getenv(char *var_name);
int _strcmp(char *first, char *second);
void _exit_func(char **argv);
int built_in_check(char *arg);
void handle_built_in(char **argv);
int _atoi(char *s);
char *first_arg_handler(char **ret_bfr);
char **_strtok(char *bfr, char *delim);
void _env_func(char **argv);
char *_substr(char *str, unsigned int start, unsigned int end);
env_typ_t _genv_max(char *var_name);
unsigned int _strarrlen(char **arr);
void _setenv_old(char *name, unsigned int len, unsigned int idx, char *val);
void _setenv_new(char *name, unsigned int len, char *val);
void _setenv(char **argv);
void _unsetenv(char **argv);
int _strincludesstr(char *buffer, char *snippet);
void _cd(char **argv);
void _echo(char **argv);
void free_mult(char **argv);
void space_end(unsigned int *nbidx, unsigned int *i, char *str_bfr, char *str);
int is_space_only(char *str);
char *strip_spaces(char *str);
int mid_newline(char *bfr);

#endif
