#include "shell.h"

/**
 * expansion - Destructures arguments
 * @inp_struct: Shell command data
 * Return: void
 */
void expansion(inp_typ *inp_struct)
{
	int i, j, k;
	char *str, *value;

	for (i = 0; inp_struct->arr[i]; i++)
	{
		if (_strcmp(inp_struct->arr[i], "$$") == 0)
		{
			free(inp_struct->arr[i]);
			str = _itoa(inp_struct->pid);
			inp_struct->arr[i] = _strdup(str);
			free(str);
		}
		else if (_strcmp(inp_struct->arr[i], "$?") == 0)
		{
			free(inp_struct->arr[i]);
			str = _itoa(inp_struct->status);
			inp_struct->arr[i] = _strdup(str);
			free(str);
		}
		else if (inp_struct->arr[i][0] == '$')
		{
			str = malloc(sizeof(char) * _strlen(inp_struct->arr[i]));
			for (j = 1, k = 0; inp_struct->arr[i][j]; j++, k++)
				str[k] = inp_struct->arr[i][j];
			str[k] = '\0';
			value = _getenv(inp_struct, str);
			if (value == NULL)
			{
				free(value);
				free(str);
			}
			else
			{
				free(inp_struct->arr[i]);
				free(str);
				inp_struct->arr[i] = _strdup(value);
				free(value);
			}
		}
	}
}

/**
 * push_path_node - Appends a new node to a path list
 * @head: Path pointer
 * @str: String to appen
 * Return: New list address
 */
path_typ *push_path_node(path_typ **head, char *str)
{
	path_typ *paths, *tmp;

	tmp = *head;
	paths = malloc(sizeof(path_typ));

	if (!paths)
		return (NULL);

	paths->s = _strdup(str);
	paths->next = NULL;

	if (!tmp)
	{
		*head = paths;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = paths;
	}

	return (*head);
}

/**
 * serialize_path - serialize paths in path env var
 * @inp_struct: shell data
 * Return: path env var
 */
path_typ *serialize_path(inp_typ *inp_struct)
{
	char path[5] = "PATH";
	int i, j, k, check;
	path_typ *head = NULL;
	char *str;

	for (i = 0; inp_struct->_env[i]; i++)
	{
		j = 0, check = 0;
		while (inp_struct->_env[i][j] != '=' && path[j] != '\0')
		{
			if (inp_struct->_env[i][j] != path[j])
				check = 1;
			j++;
		} k = 0;
		if (check == 0)
		{
			j++;
			while (inp_struct->_env[i][j])
			{
				if (inp_struct->_env[i][j] == ':')
				{
					str[k] = '\0', k = 0;
					push_path_node(&head, str);
					free(str);
				}
				else
				{
					if (k == 0)
						str = malloc(sizeof(char) * 150);
					str[k] = inp_struct->_env[i][j], k++;
				} j++;
			} str[k] = '\0';
			push_path_node(&head, str);
			free(str);
			break;
		}
	} str = _getenv(inp_struct, "PWD");
	push_path_node(&head, str);
	free(str);
	return (head);
}

/**
 * scan_paths - Scan for executable
 * @path_l: Path data
 * @fd: File to scan
 * Return: Full path name
 */
char *scan_paths(path_typ *path_l, char *fd)
{
	path_typ *tmp = path_l;
	char *path;
	struct stat s;

	while (tmp)
	{
		path = malloc(sizeof(char) * (_strlen(tmp->s) + _strlen(fd) + 2));

		if (fd[0] == '/')
		{
			free(path);
			if (stat(fd, &s) == 0)
			{
				path = _strdup(fd);
				return (path);
			}
			else
				return (NULL);
		}

		_strcpy(path, tmp->s);
		_strcat(path, "/");
		_strcat(path, fd);
		if (stat(path, &s) == 0)
			return (path);

		free(path);
		tmp = tmp->next;
	}

	return (NULL);
}
