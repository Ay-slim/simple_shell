#include "shell.h"

/**
 * _cd - Change pwd
 * @inp_struct: input data to shell
 * Return: an exit value
 */
int _cd(inp_typ *inp_struct)
{
	int i, j = 0;
	char *new_pwd, *old_pwd = _getenv(inp_struct, "PWD");

	if (inp_struct->arr[1] == NULL)
	{
		free_arr_o_arr(inp_struct->arr);
		inp_struct->arr = malloc(sizeof(char *) * 3);
		inp_struct->arr[0] = _strdup("cd");
		inp_struct->arr[1] = _getenv(inp_struct, "HOME");
		inp_struct->arr[2] = NULL;
	}
	else if (_strcmp(inp_struct->arr[1], "-") == 0)
	{
		free(inp_struct->arr[1]);
		inp_struct->arr[1] = _getenv(inp_struct, "OLDPWD");
		j++;
	}
	if (inp_struct->arr[1] == NULL)
		j = _writeerr(inp_struct, 1);
	else
	{
		i = chdir(inp_struct->arr[1]);
		if (i == -1)
		{
			_writeerr(inp_struct, 1);
			free(old_pwd);
			return (2);
		}
	}
	if (j == 1)
	{
		write(STDOUT_FILENO, inp_struct->arr[1], _strlen(inp_struct->arr[1]));
		write(STDOUT_FILENO, "\n", 1);
	} new_pwd = getcwd(NULL, 1024);
	_setdir(inp_struct, "new", new_pwd);
	_setdir(inp_struct, "old", old_pwd);
	free(new_pwd);
	free(old_pwd);
	return (0);
}

/**
 * _custexit - Quit the shell
 * @inp_struct: Holds input data
 * Return: Exits with specified exit status
 */
int _custexit(inp_typ *inp_struct)
{
	int exit_status = inp_struct->status;

	if (inp_struct->interact == 1)
	{
		if (!_strcmp("exit", inp_struct->arr[0]) && inp_struct->arr[1])
		{
			inp_struct->status = _atoi(inp_struct->arr[1]);
			exit_status = inp_struct->status;
		}
	}
	if (inp_struct->path)
		free_list(inp_struct->path);

	if (inp_struct->av)
		free_arr_o_arr(inp_struct->av);
	if (inp_struct->_env)
		free_arr_o_arr(inp_struct->_env);
	if (inp_struct->arr && inp_struct->interact == 1)
		free_arr_o_arr(inp_struct->arr);
	if (inp_struct->line)
		free(inp_struct->line);

	exit(exit_status);
}

/**
 * _custenv - Returns env variables
 * @inp_struct: Shell input data
 * Return: Int 0
 */
int _custenv(inp_typ *inp_struct)
{
	int i;
	int len;

	for (i = 0; inp_struct->_env[i]; i++)
	{
		len = _strlen(inp_struct->_env[i]);
		write(STDOUT_FILENO, inp_struct->_env[i], len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * _set - Sets env variable
 * @inp_struct: Shell input value
 * Return: 0 or 12
 */
int _set(inp_typ *inp_struct)
{
	int i, j, b, k = 0, check, end = 0;
	char **new_env;

	for (i = 0; inp_struct->_env[i]; i++)
		;
	if (inp_struct->arr[1] == NULL || inp_struct->arr[2] == NULL)
		return (_writeerr(inp_struct, 2));
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (12);
	for (i = 0; inp_struct->_env[i]; i++)
	{
		j = 0, check = 0;
		b = (inp_struct->_env[i][j] != '=' && inp_struct->arr[1][j] != '\0');
		while (b)
		{
			if (inp_struct->_env[i][j] != inp_struct->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			new_env[k] = _setenv(inp_struct);
			k++, end = 1;
			continue;
		}
		new_env[k] = _strdup(inp_struct->_env[i]);
		k++;
	}
	if (end == 0)
	{
		new_env[k] = _setenv(inp_struct);
		new_env[k + 1] = NULL;
	}
	else
		new_env[k] = NULL;
	free_arr_o_arr(inp_struct->_env);
	inp_struct->_env = new_env;
	return (0);
}

/**
 * _unset - Removes an env variable
 * @inp_struct: Input data to shell
 * Return: 0 or -1
 */
int _unset(inp_typ *inp_struct)
{
	int i, j, b, k = 0, check, end = 0;
	char **new_env;

	for (i = 0; inp_struct->_env[i]; i++)
		;
	if (inp_struct->arr[1] == NULL)
		return (_writeerr(inp_struct, 3));
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (12);
	for (i = 0; inp_struct->_env[i]; i++)
	{
		j = 0, check = 0;
		b = (inp_struct->_env[i][j] != '=' && inp_struct->arr[1][j] != '\0');
		while (b)
		{
			if (inp_struct->_env[i][j] != inp_struct->arr[1][j])
				check = 1;
			j++;
		}
		if (check == 0)
		{
			end = 1;
			continue;
		}
		new_env[k] = _strdup(inp_struct->_env[i]);
		k++;
	}
	new_env[k] = NULL;
	if (end == 0)
	{
		perror("Environment variable does not exist\n");
		free_arr_o_arr(new_env);
		return (6);
	}
	free_arr_o_arr(inp_struct->_env);
	inp_struct->_env = new_env;
	return (0);
}
