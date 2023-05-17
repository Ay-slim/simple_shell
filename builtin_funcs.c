#include "shell.h"

/**
 * _exit_func - It executes the exit builtin command
 * @argv: Array of argument strings
 * Return: Nothing
 */
void _exit_func(char **argv)
{
	unsigned int i = 0;

	if (argv[1])
		i = _atoi(argv[1]);
	exit(i);
}

/**
 * _env_func - Executes the env builtin
 * @argv: Array of argument strings
 * Return: Nothing
 */
void _env_func(char **argv)
{
	unsigned int i = 0;
	unsigned int len = _strarrlen(environ);
	(void)(argv);

	while (i < len)
	{
		_putstr(environ[i], 1);
		i++;
		_putchar('\n', 1);
	}
}

/**
 * _setenv - Executes the setenv builtin
 * @argv: Array of arg strings
 * Return: Nothing
 */
void _setenv(char **argv)
{
	env_typ_t ex_env;

	if (_strarrlen(argv) != 3)
	{
		_putstr("Invalid number of arguments to setenv\n", 2);
		return;
	}
	ex_env = _genv_max(argv[1]);
	if (!ex_env.idx)
		_setenv_new(argv[1], ex_env.len, argv[2]);
	else
		_setenv_old(argv[1], ex_env.len, ex_env.idx, argv[2]);
}

/**
 * _unsetenv - Executes unsetenv
 * @argv: Array of arg strings
 * Return: Nothing
 */
void _unsetenv(char **argv)
{
	env_typ_t ex_env;
	char **env;
	int i = 0;
	int j = 0;

	if (_strarrlen(argv) != 2)
	{
		_putstr("Invalid number of arguments to setenv\n", 2);
		return;
	}
	ex_env = _genv_max(argv[1]);
	env = malloc((ex_env.len - 1) * sizeof(char *));
	if (!env)
		exit(1);
	while (i < (ex_env.len - 1))
	{
		if (i == ex_env.idx)
		{
			j++;
			continue;
		}
		env[i] = malloc((_strlen(environ[j]) + 1) * sizeof(char));
		_strcpy(environ[j], env[i]);
		i++;
		j++;
	}
	env[ex_env.len - 1] = NULL;
	environ = env;
}

/**
 * _cd - Change directory
 * @argv: Array of arg strings
 * Return: Nothing
 */
void _cd(char **argv)
{
	const char *path = argv[1];
	char *tp = argv[1];
	char *v_path = argv[1];
	unsigned int l;
	env_typ_t pwd_deets = _genv_max("PWD");
	char *curr_dir = pwd_deets.val;
	int idx = pwd_deets.idx;
	int len = pwd_deets.len;
	unsigned int argc = _strarrlen(argv);

	if (argc == 1)
		v_path = _getenv("HOME");
	if (argc > 1 && _strcmp(argv[1], "-"))
		v_path = _getenv("OLDPWD");
	if (argc > 1 && !_strcmp(argv[1], "-") && !_strcmp(argv[1], "-"))
	{
		if (!_strincludes(tp, '/'))
		{
			v_path = _pathconcat(curr_dir, '/', tp);
		}
		else if (tp[0] == '.' && tp[1] == '/')
		{
			l = _strlen(tp);
			v_path = _pathconcat(curr_dir, '/',  _substr(tp, 2, l));
		}
	}
	path = v_path;
	if (chdir(path) == -1)
	{
		_putstr("Error changing directory\n", 2);
	}
	else
	{
		_setenv_old("PWD", len, idx, v_path);
	}
}

