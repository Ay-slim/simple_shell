#include "shell.h"

/**
 * handle_builtin - Handles built in commands
 * @arr: Assembly of shell commands
 * Return: Function linked with appropriate builtin comand
 */
int (*handle_builtin(char **arr))(inp_typ *)
{
	built_in shell_map[] = {
		{"exit", _custexit},
		{"env", _custenv},
		{"setenv", _set},
		{"unsetenv", _unset},
		{"cd", _cd},
		{NULL, NULL}
	};

	int i = 0;

	if (arr != NULL)
	{
		while (shell_map[i].func != NULL)
		{
			if (_strcmp(shell_map[i].str, arr[0]) == 0)
			{
				return (shell_map[i].func);
			}
			else
				i++;
		}
	}

	return (NULL);
}

/**
 * isnotatty - Working with the non interactive shell
 * @inp_struct: Shell data input
 * Return: Nothing
 */
void isnotatty(inp_typ *inp_struct)
{
	char *path;

	inp_struct->interact = 0;
	for (; ;)
	{
		path = parse_cmd(inp_struct);
		if (!path && inp_struct->builtin == 0)
			_custexit(inp_struct);
		else if (!path && inp_struct->builtin == 1)
			continue;

		inp_struct->builtin = 0;
		inp_struct->pid = fork();
		if (inp_struct->pid == 0)
		{
			inp_struct->status = execve(path, inp_struct->arr, inp_struct->_env);
			if (inp_struct->status == -1)
			{
				write(STDERR_FILENO, inp_struct->av[0], _strlen(inp_struct->av[0]));
				write(STDERR_FILENO, ": ", 2);
				write(STDERR_FILENO, inp_struct->arr[0], _strlen(inp_struct->av[0]));
				write(STDERR_FILENO, ": Permission denied\n", 20);
				free(path);
				inp_struct->status = 13;
				_custexit(inp_struct);
			}
		}
		else
		{
			wait(&inp_struct->status);
			inp_struct->status = WEXITSTATUS(inp_struct->status);
		}
		free_arr_o_arr(inp_struct->arr);
		free(path);
	}
}

/**
 * shell_core - Loops the interactive shell
 * @in_st: Shell input data
 * Return: Nothing
 */
void shell_core(inp_typ *in_st)
{
	char *path;

	if (in_st->av[1])
		exit(98);
	else if (!isatty(STDIN_FILENO))
		isnotatty(in_st);
	else
	{
		for (; ;)
		{
			write(STDOUT_FILENO, "($) ", 4);
			fflush(stdout);
			path = parse_cmd(in_st);
			if (!path)
				continue;
			in_st->pid = fork();
			if (in_st->pid == 0)
			{
				in_st->status = execve(path, in_st->arr, in_st->_env);
				if (in_st->status == -1)
				{
					write(STDERR_FILENO, in_st->av[0], _strlen(in_st->av[0]));
					write(STDERR_FILENO, ": ", 2);
					write(STDERR_FILENO, in_st->arr[0], _strlen(in_st->arr[0]));
					write(STDERR_FILENO, ": Permission denied\n", 20);
					free(path);
					in_st->status = 13;
					_custexit(in_st);
				}
			}
			else
			{
				wait(&in_st->status);
				in_st->status = WEXITSTATUS(in_st->status);
			}
			free_arr_o_arr(in_st->arr);
			free(path);
		}
	}
}

/**
 * parse_cmd - Parses shell commands
 * @in_sh: Shell data structure
 * Return: Path to executable
 */
char *parse_cmd(inp_typ *in_sh)
{
	int (*native_f)(inp_typ *in_sh);
	char *path;

	in_sh->arr = _readcmd(in_sh, in_sh->line, in_sh->length);
	if (!in_sh->arr)
	{
		free(in_sh->line);
		return (NULL);
	}
	expansion(in_sh);
	native_f = handle_builtin(in_sh->arr);

	if (native_f != NULL)
	{
		in_sh->status = native_f(in_sh);
		if (in_sh->arr != NULL)
			free_arr_o_arr(in_sh->arr);
		in_sh->builtin = 1;
		return (NULL);
	}
	path = scan_paths(in_sh->path, in_sh->arr[0]);

	if (!path)
	{
		write(STDERR_FILENO, in_sh->av[0], _strlen(in_sh->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, in_sh->arr[0], _strlen(in_sh->arr[0]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		in_sh->status = 2;
		free_arr_o_arr(in_sh->arr);
		free(path);
		return (NULL);
	}
	return (path);
}

/**
 * main - Main function
 * @ac: Number of arguments
 * @av: Array of args
 * @env: Env variables
 *
 * Return: 0 at successful exit
 */
int main(int ac, char *av[], char *env[])
{
	inp_typ in_st;
	int j;

	in_st.line = NULL;
	in_st.length = 0;
	in_st.interact = 1;
	in_st.pid = getpid();
	in_st.status = 0;
	in_st.builtin = 0;
	in_st.arr = NULL;
	(void) env;

	in_st.av = malloc(sizeof(char *) * (ac + 1));
	for (j = 0; av[j]; j++)
		in_st.av[j] = _strdup(av[0]);
	in_st.av[j] = NULL;
	for (j = 0; environ[j]; j++)
		;

	in_st._env = malloc(sizeof(char *) * (j + 1));
	for (j = 0; environ[j]; j++)
		in_st._env[j] = _strdup(environ[j]);
	in_st._env[j] = NULL;

	in_st.path = serialize_path(&in_st);

	shell_core(&in_st);

	return (0);
}
