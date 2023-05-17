#include "shell.h"

/**
 * _is_digit - Function to check if a character is digit
 * @c: Char to test
 * Return: 1 if digit 0 otherwise
 */

int _is_digit(char c)
{
	int diff = c - '0';

	return (diff >= 0 && diff < 10);
}
/**
 * _atoi - Function to return integer within a string
 * @s: Source string
 * Return: The integer within the string
 */

int _atoi(char *s)
{
	float place_value;
	float sum;
	float multiplier;
	int length;
	int i = 0;
	int sign;

	place_value = 1;
	sum = 0;
	sign = 1;
	length = _strlen(s);
	multiplier = 0.1;
	while (i < length)
	{
		if (s[i] == '-' && _is_digit(s[i + 1]))
		{
			sign = -1;
		}
		if (_is_digit(s[i]))
		{
			sum += ((s[i] - '0') * place_value);
			place_value /= 10;
			multiplier *= 10;
			if (!_is_digit(s[i + 1]))
			{
				break;
			}
		}
		i++;
	}
	return ((int)(sum * sign * multiplier));
}

/**
 * first_arg_handler - Handles first arg
 * @ret_bfr: Return buffer from calling function
 * Return: Lead path or null
 */
char *first_arg_handler(char **ret_bfr)
{
	if (built_in_check(ret_bfr[0]))
	{
		handle_built_in(ret_bfr);
		return (NULL);
	}
	return (handle_path(ret_bfr[0]));
}

/**
 * _strtok - Strtok implementation
 * @bfr: String to split up
 * @delim: Delimiter
 * Return: An array of strings separated by the delimiter
 */
char **_strtok(char *bfr, char *delim)
{
	char **argv;
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int b_len = _strlen(bfr);
	unsigned int d_len = _strlen(delim);
	unsigned int k = 0;
	int cmp = 0;

	argv = malloc(100 * sizeof(char));
	if (!argv)
		exit(1);
	argv[0] = malloc(100 * sizeof(char));
	if (!argv[0])
		exit(1);
	while (k < b_len)
	{
		cmp = _strcmp(_substr(bfr, k, k + d_len), delim);
		if ((k == 0 || k == (b_len - d_len)) && cmp)
		{
			k++;
			continue;
		}
		if (cmp)
		{
			argv[i][j] = '\0';
			j = 0;
			i++;
			k += d_len;
			argv[i] = malloc(100 * sizeof(char));
			if (!argv[i])
				exit(1);
			continue;
		}
		argv[i][j] = bfr[k];
		j++;
		k++;
	}
	argv[i + 1] = NULL;
	return (argv);
}

/**
 * _strarrlen - Returns the length of an array of strings
 * @arr: Array of strings
 * Return: Length of array
 */
unsigned int _strarrlen(char **arr)
{
	char **temp = arr;
	unsigned int i = 0;

	while (*temp)
	{
		i++;
		temp++;
	}
	return (i);
}


