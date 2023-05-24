#include "shell.h"

/**
 * _strlen - Gets the length of a string
 * @s: String to measure
 * Return: String length
 */
int _strlen(char *s)
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
 * _strcat - Concats two strings
 * @sink: string to concat with
 * @src: buffer to join
 * Return: Combined string
 */
char *_strcat(char *sink, char *src)
{
	int i;
	int j;

	for (i = 0; sink[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++, i++)
	{
		sink[i] = src[j];
	}

	sink[i] = '\0';
	return (sink);
}

/**
 * _strcpy - copies a string from one buffer to the other
 * @sink: Sink buffer
 * @src: Source buffer
 * Return: pointer to sink
 */
char *_strcpy(char *sink, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		sink[i] = src[i];

	sink[i] = '\0';
	return (sink);
}

/**
 * _strcmp - compares two strings
 * @first_str: First string
 * @sec_str: Second string
 * Return: -1 if fails, 1 if the same
 */
int _strcmp(char *first_str, char *sec_str)
{
	int n;
	int j;

	for (n = 0, j = 0; (first_str[n] != '\0' || sec_str[n] != '\0'); n++)
	{
		j = first_str[n] - sec_str[n];
		if (j != 0)
			break;
	}

	if (j < 0)
		return (-1);
	else if (j > 0)
		return (1);

	return (j);
}

/**
 * _strdup - Clones a string
 * @s: String to clone
 * Return: Cloned string
 */
char *_strdup(char *s)
{
	char *dup;
	size_t len;

	len = _strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	_dataclone(dup, s, len + 1);
	return (dup);
}

