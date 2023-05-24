#include "shell.h"

/**
 * _getenv - Return an env variable
 * @inp_struct: Struct holding input values
 * @name: Name of variable to return
 * Return: Pointer to the value of env
 */

char *_getenv(inp_typ *inp_struct, char *name)
{
	int i, j, k, l, check;
	char *val;

	for (i = 0; inp_struct->_env[i]; i++)
	{
		j = 0, check = 0;
		while (inp_struct->_env[i][j] != '=' && name[j] != '\0')
		{
			if (inp_struct->_env[i][j] != name[j])
				check = 1;
			j++;
		}
		if (check == 0 && inp_struct->_env[i][j] == '=')
		{
			for (k = j + 1, l = 0; inp_struct->_env[i][k]; k++, l++)
				;

			val = malloc(sizeof(char) * (l + 1));

			for (k = j + 1, l = 0; inp_struct->_env[i][k]; l++, k++)
				val[l] = inp_struct->_env[i][k];
			val[l] = '\0';
			return (val);
		}
	}

	return (NULL);
}

/**
 * _setenv - Sets an env value
 * @inp_struct: Struct holding the input
 * Return: Updated env
 */
char *_setenv(inp_typ *inp_struct)
{
	char *s;
	int first_len;
	int sec_len;

	first_len = _strlen(inp_struct->arr[1]);
	sec_len = _strlen(inp_struct->arr[2]);

	s = malloc(sizeof(char) * (first_len + sec_len + 2));
	if (!s)
		return (NULL);

	_strcpy(s, inp_struct->arr[1]);
	_strcat(s, "=");
	_strcat(s, inp_struct->arr[2]);

	return (s);
}

/**
 * _setdir - Sets a directory
 * @inp_struct: Struct holding the input
 * @olddir: Directory to change
 * @newdir: new directory
 * Return: Nothing
 */
void _setdir(inp_typ *inp_struct, char *olddir, char *newdir)
{
	free_arr_o_arr(inp_struct->arr);
	inp_struct->arr = malloc(sizeof(char *) * 4);
	inp_struct->arr[0] = _strdup("setenv");

	if (_strcmp(olddir, "old") == 0)
		inp_struct->arr[1] = _strdup("OLDPWD");
	else if (_strcmp(olddir, "new") == 0)
		inp_struct->arr[1] = _strdup("PWD");

	inp_struct->arr[2] = _strdup(newdir);
	inp_struct->arr[3] = NULL;

	_set(inp_struct);
}

/**
 * _writeerr - Writes to stderr
 * @inp_struct: Input data to shell
 * @i: Input value
 * Return: Integer
 */
int _writeerr(inp_typ *inp_struct, int i)
{
	if (i == 1)
	{
		write(STDERR_FILENO, inp_struct->av[0], _strlen(inp_struct->av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, inp_struct->arr[0], 2);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, inp_struct->arr[1], _strlen(inp_struct->arr[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (1);
	}

	if (i == 2)
	{
		write(STDERR_FILENO, inp_struct->av[0], _strlen(inp_struct->av[0]));
		write(STDERR_FILENO, ": Usage: setenv VARIABLE VALUE\n", 31);
		return (1);
	}

	if (i == 3)
	{
		write(STDERR_FILENO, inp_struct->av[0], _strlen(inp_struct->av[0]));
		write(STDERR_FILENO, ": Usage: unsetenv VARIABLE\n", 27);
		return (1);
	}

	if (i == 4)
	{
		write(STDOUT_FILENO, inp_struct->arr[1], _strlen(inp_struct->arr[1]));
		write(STDOUT_FILENO, ": OLDPWD not set\n", 17);
		return (0);
	}

	return (1);
}
