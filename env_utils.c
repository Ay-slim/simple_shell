#include "shell.h"

/**
 * name_val - Returns index of name being sought
 * @env: Current env string
 * @name_len: Length of env name
 * Return: Env value
 */
char *name_val(char *env, unsigned int name_len)
{
	unsigned int i = 0;
	unsigned int val_len = _strlen(env) - name_len;
	char *ret_val;

	ret_val = malloc(val_len * sizeof(char));
	if (!ret_val)
		return (NULL);
	while (i < val_len - 1)
	{
		ret_val[i] = (env)[i + name_len + 1];
		i++;
	}
	ret_val[val_len - 1] = '\0';
	return (ret_val);
}

/**
 * _genv_max - Returns a struct with env length, index, and value
 * @var_name: Name of env value to check
 * Return: Env_typ_t value with length, index, and value
 */
env_typ_t _genv_max(char *var_name)
{
	unsigned int j = 0;
	unsigned int len = 0;
	unsigned int name_len = _strlen(var_name);
	unsigned int idx = 0;
	char *env_val = NULL;
	char **env = environ;
	env_typ_t env_deets;

	while (*env)
	{
		j = 0;
		while (!idx && (j < name_len))
		{
			if (j == name_len - 1 && var_name[j] == (*env)[j])
			{
				idx = len;
				env_val = name_val(*env, name_len);
				break;
			}
			if (var_name[j] != (*env)[j])
				break;
			j++;
		}
		env++;
		len++;
	}
	env_deets.val = env_val;
	env_deets.idx = idx;
	env_deets.len = len;
	return (env_deets);
}

/**
 * _setenv_old - Set an already existing env var
 * @name: Name of variable to set
 * @len: Environ length
 * @idx: Index to set
 * @val: Value to set
 * Return: Void
 */
void _setenv_old(char *name, unsigned int len, unsigned int idx, char *val)
{
	char *val_to_add = _pathconcat(name, '=', val);
	char **env = malloc((len + 1) * sizeof(char *));
	unsigned int i = 0;
	unsigned int j;
	unsigned int k;

	if (!env)
		exit(1);
	while (i < len)
	{
		if (i == idx)
		{
			j = _strlen(val_to_add);
			env[i] = malloc((j + 1) * sizeof(char));
			if (!env[i])
				exit(1);
			_strcpy(val_to_add, env[i]);
		}
		else
		{
			k = _strlen(environ[i]);
			env[i] = malloc((k + 1) * sizeof(char));
			if (!env[i])
				exit(1);
			_strcpy(environ[i], env[i]);
		}
		i++;
	}
	env[len] = NULL;
	environ = env;
}

/**
 * _setenv_new - Set a new env var
 * @name: Name of variable to set
 * @len: Environ length
 * @val: Value to set
 * Return: Void
 */
void _setenv_new(char *name, unsigned int len, char *val)
{
	char *val_to_add = _pathconcat(name, '=', val);
	char **env = malloc((len + 1) * sizeof(char *));
	unsigned int i = 0;

	if (!env)
		exit(1);
	while ((i < len) && environ[i])
	{
		env[i] = malloc((_strlen(environ[i]) + 1) * sizeof(char));
		if (!env[i])
			exit(1);
		_strcpy(environ[i], env[i]);
		i++;
	}
	env[len] = malloc((_strlen(val_to_add) + 1) * sizeof(char));
	if (!env[len])
		exit(1);
	_strcpy(val_to_add, env[len]);
	env[len + 1] = NULL;
	environ = env;
}

