#include "shell.h"

/**
 * _strlen - Gets the length of a string
 * @s: String to measure
 * Return: String length
 */
unsigned int _strlen(char *s)
{
	unsigned int len = 0;
	char *temp = s;

	while (*temp)
	{
		len++;
		temp++;
	}
	return (len);
}

/**
 * _strcpy_n_o - Copy a string and replace new line with null terminator
 * @src: Source buffer
 * @sink: Buffer to copy to
 * Return: Nothing
 */
void _strcpy_n_o(char *src, char *sink)
{
	unsigned int len = _strlen(src);
	unsigned int i = 0;

	while (i < len)
	{
		if (src[i] == '\n')
		{
			sink[i] = '\0';
			return;
		}
		else
		{
			sink[i] = src[i];
		}
		i++;
	}
	sink[len] = '\0';
}

/**
 * _strincludes - Indicates whether a string contains a certain char
 * @s: String to check
 * @c: Char to look up
 * Return: 0 or 1
 */
int _strincludes(char *s, char c)
{
	while (*s)
	{
		if (c == *s)
			return (1);
		s++;
	}
	return (0);
}

/**
 * _pathconcat - Concatenates two strings
 * @first: First string
 * @link: Linking char
 * @second: Second string
 * Return: Concatenated string
 */
char *_pathconcat(char *first, char link, char *second)
{
	unsigned int len = _strlen(first) + _strlen(second);
	char *ret_bfr = malloc((len + 2) * sizeof(char));
	unsigned int cpy_tracker = 0;

	if (!ret_bfr)
		return (NULL);
	while (*first)
	{
		ret_bfr[cpy_tracker] = *first;
		first++;
		cpy_tracker++;
	}
	ret_bfr[cpy_tracker] = link;
	cpy_tracker++;
	while (*second)
	{
		ret_bfr[cpy_tracker] = *second;
		second++;
		cpy_tracker++;
	}
	ret_bfr[cpy_tracker] = '\0';
	return (ret_bfr);
}

/**
 * _strcmp - Compares two strings
 * @first: First string
 * @second: Second string
 * Return: 1 if the strings are the same 0 otherwise
 */
int _strcmp(char *first, char *second)
{
	unsigned int i = 0;
	unsigned int first_len = _strlen(first);
	unsigned int second_len = _strlen(second);

	if (first_len != second_len)
		return (0);
	while (i < first_len)
	{
		if (first[i] != second[i])
			return (0);
		i++;
	}
	return (1);
}

