#include "shell.h"

/**
 * _substr - Returns a substring specified by start and end indices
 * @str: Main string to sub from
 * @start: Start index
 * @end: End index (not included)
 * Return: Sub string
 */
char *_substr(char *str, unsigned int start, unsigned int end)
{
	char *ret_bfr;
	unsigned int ret_bfr_len = end - start + 1;
	unsigned int i = 0;

	ret_bfr = malloc(ret_bfr_len * sizeof(char));
	if (ret_bfr == NULL)
		exit(1);
	while (i < ret_bfr_len - 1)
	{
		ret_bfr[i] = str[start + i];
		i++;
	}
	ret_bfr[ret_bfr_len - 1] = '\0';
	return (ret_bfr);
}

/**
 * _strcpy - Copy a string
 * @src: Source buffer
 * @sink: Buffer to copy to
 * Return: Nothing
 */
void _strcpy(char *src, char *sink)
{
	unsigned int len = _strlen(src);
	unsigned int i = 0;

	while (i < len)
	{
		sink[i] = src[i];
		i++;
	}
	sink[len] = '\0';
}

/**
 * _strincludesstr - Checks if a set of chars are present in a string
 * @buffer: Main string to check
 * @snippet: Sub string to check for
 * Return: 1 if present 0 otherwise
 */
int _strincludesstr(char *buffer, char *snippet)
{
	unsigned int j = 0;
	unsigned int i = 0;
	unsigned int sub_len = _strlen(snippet);
	unsigned int bfr_len = _strlen(buffer);
	unsigned int found_var = 0;

	while (i < (bfr_len - sub_len))
	{
		j = 0;
		while (j < sub_len)
		{
			if (j == sub_len - 1 && snippet[j] == buffer[j + i])
			{
				found_var = 1;
				break;
			}
			if (snippet[j] != buffer[j + i])
				break;
			j++;
		}
		if (found_var)
			return (found_var);
		i++;
	}
	return (0);
}

