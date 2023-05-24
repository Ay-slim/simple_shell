#include "shell.h"

/**
 * _strincludes - Checks if a string includes a character
 * @str: String to check
 * @c: Character to search
 * @len: String length
 * Return: Nothing
 */
void *_strincludes(const void *str, int c, size_t len)
{
	const unsigned char *tmp = (const unsigned char *)str;

	while (len-- > 0)
	{
		if (*tmp == c)
			return ((void *)tmp);
		tmp++;
	}
	return (NULL);
}

/**
 * _strtok - String tokenization by delimiter
 * @str: String to tokenize
 * @delim: Delimiter
 * Return: Tokenized string
 */
char *_strtok(char *str, const char *delim)
{
	static char *s;
	char *ret_val = NULL;

	if (str != NULL)
	{
		s = str;
	}
	if (s != NULL && _strlen(s))
	{
		const size_t len = _strlen((char *)delim);

		while (*s && _strincludes(delim, *s, len) != NULL)
		{
			++s;
		}
		if (*s)
		{
			ret_val = s;
			while (*s)
			{
				if (_strincludes(delim, *s, len) != NULL)
				{
					break;
				}
				else
					++s;
			}
			if (*s)
			{
				s[0] = 0;
				++s;
			}
		}
	}
	return (ret_val);
}

/**
 * _dataclone - Clones data from one memory location to the other
 * @sink: Data destination
 * @src: Data origin
 * @len: Data size
 * Return: Nothing
 */
void _dataclone(void *sink, const void *src, unsigned int len)
{
	char *ptr = (char *)src;
	char *tmp = (char *)sink;
	unsigned int i;

	for (i = 0; i < len; i++)
		tmp[i] = ptr[i];
}

/**
 * _realloc - Custom memory reallocation
 * @mem: Previous memory location
 * @prev_len: Previous memory length
 * @new_len: New length
 * Return: New memory pointer
 */
void *_realloc(void *mem, unsigned int prev_len, unsigned int new_len)
{
	char *tmp;
	unsigned int i;

	if (new_len == prev_len)
		return (mem);

	if (mem == NULL)
	{
		mem = malloc(new_len);
		return (mem);
	}

	if (new_len == 0 && mem != NULL)
	{
		free(mem);
		return (NULL);
	}

	tmp = malloc(new_len);
	if (tmp == NULL)
		return (NULL);

	for (i = 0; i < new_len && i < prev_len; i++)
		;

	_dataclone(tmp, mem, i);
	free(mem);

	return (tmp);
}

