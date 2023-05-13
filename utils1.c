#include "shell.h"

/**
 * _getenv - Returns the value of a given env variable
 * @var_name: Variable to get value for
 * Return: Env var string or NULL if not found
 */
char *_getenv(char *var_name)
{
	unsigned int j = 0;
	unsigned int i = 0;
	unsigned int name_len = _strlen(var_name);
	unsigned int found_var = 0;
	char *ret_val;
	unsigned int val_len;
	char **env = environ;

	while (*env)
	{
		j = 0;
		while (j < name_len)
		{
			if (j == name_len - 1 && var_name[j] == (*env)[j])
			{
				found_var = 1;
				break;
			}
			if (var_name[j] != (*env)[j])
				break;
			j++;
		}
		if (found_var)
		{
			val_len = _strlen(*env) - name_len;
			ret_val = malloc(val_len * sizeof(char));
			if (!ret_val)
				return (NULL);
			while (i < val_len - 1)
			{
				ret_val[i] = (*env)[i + name_len + 1];
				i++;
			}
			ret_val[val_len - 1] = '\0';
			return (ret_val);
		}
		env++;
	}
	return (NULL);
}

/**
 * built_in_check - Check if command is built in
 * @arg: Command to check
 * Return: 1 if builtin 0 otherwise
 */
int built_in_check(char *arg)
{
	unsigned int i = 0;
	char *BUILT_IN_LIST[] = {
		"exit", "env", "setenv", "unsetenv", "cd", "echo", NULL
	};

	while (BUILT_IN_LIST[i])
	{
		if (_strcmp(BUILT_IN_LIST[i], arg))
			return (1);
		i++;
	}
	return (0);
}

/**
 * handle_path - Returns valid path and exits if invalid path
 * @bfr: Buffer containing command or path passed to shell
 * Return: Valid path, NULL if command not found or path not valid
 */
char *handle_path(char *bfr)
{
	char *exec_path;
	char *path_var = _getenv("PATH");
	char **path_vals = _strtok(path_var, ":");

	if (_strincludes(bfr, '/') == 0)
	{
		while (*path_vals)
		{
			exec_path = _pathconcat(*path_vals, '/', bfr);
			if (access(exec_path, X_OK) == 0)
			{
				return (exec_path);
			}
			path_vals++;
		}
		_putstr("Invalid command or path\n", 2);
		return (NULL);
	}
	else
	{
		if (access(bfr, X_OK) == 0)
		{
			return (bfr);
		}
		_putstr("Invalid command or path\n", 2);
		return (NULL);
	}
}

/**
 * handle_built_in - Handles commands that are built in
 * @argv: An array of strings
 * Return: Void
 */
void handle_built_in(char **argv)
{
	built_in_t built_in_vals[] = {
		{"exit", _exit_func},
		{"env", _env_func},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"echo", _echo},
		{NULL, NULL}
	};
	unsigned int i = 0;

	while (built_in_vals[i].name)
	{
		if (_strcmp(built_in_vals[i].name, argv[0]))
		{
			built_in_vals[i].f(argv);
			break;
		}
		i++;
	}
}

/**
 * extract_term_args - Extract term args from stdin
 * @stdin_bfr: Buffer containing strings from stdin
 * Return: String of strings containing term args
 */

char **extract_term_args(char *stdin_bfr)
{
	char *str;
	char *lead_path;
	char **ret_bfr = NULL;

	if (stdin_bfr[0] == '\n' || is_space_only(stdin_bfr))
		return (NULL);
	str = malloc((_strlen(stdin_bfr) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	_strcpy_n_o(stdin_bfr, str);
	ret_bfr = _strtok(strip_spaces(str), " ");
	lead_path = first_arg_handler(ret_bfr);
	if (lead_path == NULL)
		return (NULL);
	ret_bfr[0] = realloc(ret_bfr[0], _strlen(lead_path) * sizeof(char));
	_strcpy_n_o(lead_path, ret_bfr[0]);
	free(str);
	return (ret_bfr);
}
