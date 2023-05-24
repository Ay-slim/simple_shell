#ifndef SHELL_H_
#define SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 1024
#define NEWLINE '\n'
#define DELIM_T " \t\n\a\r"

extern char **environ;

/**
 * struct path_str - Holds path variables
 * @s: Pointer to a path string
 * @next: Pointer to next node
 */
typedef struct path_str
{
	char *s;
	struct path_str *next;
} path_typ;

/**
 * struct inp - Struct to hold data about shell commands
 * @_env: A clone of the shell environ variable
 * @arr: Array of commands passed to shell
 * @status: Success or failure code with which shell exited
 * @av: Args
 * @builtin: Inspect command to see if built in
 * @interact: Checks for interactivity
 * @length: Line length
 * @line: Commands line
 * @path: All path variables
 * @pid: Shell current process id
 */
typedef struct inp
{
	char **_env;
	char **arr;
	char **av;
	char *line;
	int builtin;
	int interact;
	int status;
	path_typ *path;
	pid_t pid;
	size_t length;
} inp_typ;

/**
 * struct built_in - Builtin functions struct
 * @str: Command name
 * @func: Executor function
 */
typedef struct built_in
{
	char *str;
	int (*func)(inp_typ *);
} built_in;

int _strlen(char *s);
char *_strcat(char *sink, char *src);
char *_strcpy(char *sink, char *src);
char *_strdup(char *s);
int _strcmp(char *first_str, char *sec_str);
void free_arr_o_arr(char **bfr);
void free_list(path_typ *head);
char *_itoa(int i);
int _atoi(char *str);
int num_len(int i);
char *_getenv(inp_typ *inp_struct, char *name);
char *_setenv(inp_typ *inp_struct);
void _setdir(inp_typ *inp_struct, char *olddir, char *newdir);
int _writeerr(inp_typ *inp_struct, int i);
int _cd(inp_typ *inp_struct);
int _custexit(inp_typ *inp_struct);
int _custenv(inp_typ *inp_struct);
int _set(inp_typ *inp_struct);
int _unset(inp_typ *inp_struct);
void expansion(inp_typ *inp_struct);
path_typ *serialize_path(inp_typ *inp_struct);
char *scan_paths(path_typ *path_l, char *fd);
char **_readcmd(inp_typ *inp_struct, char *bfr, size_t n);
int _stripcmt(char **bfr);
void _putline(char **ln, size_t *n, char *bfr, size_t len);
ssize_t _getline(char **bfr, size_t *n, FILE *riv);
void *_strincludes(const void *str, int c, size_t len);
char *_strtok(char *str, const char *delim);
void _dataclone(void *sink, const void *src, unsigned int len);
void *_realloc(void *mem, unsigned int prev_len, unsigned int new_len);
int (*handle_builtin(char **arr))(inp_typ *);
void isnotatty(inp_typ *inp_struct);
path_typ *push_path_node(path_typ **head, char *str);
void shell_core(inp_typ *in_sh);
char *parse_cmd(inp_typ *in_sh);
#endif

