#include "shell.h"

/**
 * free_mult - Frees a collection of allocated memory spaces
 * @argv: Pointer to memory block to be freed
 * Return: Nothing
 */
void free_mult(char **argv)
{
	char **tmp = argv;

	if (!argv)
		return;
	while (*argv)
	{
		free(*argv);
		argv++;
	}
	free(tmp);
}

/**
 * allocator - Allocates space for strings
 * Return: Allocated memory
 */
char *allocator(void)
{
	char *ret_val = malloc(1024 * sizeof(char));

	if (!ret_val)
		exit(1);
	return (ret_val);
}

/**
 * sp - Checks if a vlue is space
 * @chr: Char to check
 * Return: 1 or 0 depending on success
 */
int sp(char chr)
{
	return (chr == ' ');
}

/**
 * is_space_only - Filter out collection of spaces
 * @str: String to check if input is a collection of spaces
 * Return: 1 if just spaces, 0 0therwise
*/
int is_space_only(char *str)
{
	char *space_str = " ";
	unsigned int len = _strlen(str);
	unsigned int i = 0;

	if (_strcmp(str, space_str))
		return (1);
	while (i < len)
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
/**
 * strip_spaces - Remove spaces from the stdin buffer
 * @str: Input buffer
 * Return: Pointer to space stripped string
 */
char *strip_spaces(char *str)
{
	char *str_bfr = allocator();
	unsigned int nbidx = 0;
	unsigned int bfr_len = _strlen(str);
	unsigned int i = 0;

	while (i < bfr_len)
	{
		if (sp(str[i]))
		{
			while (sp(str[i]) && i < bfr_len)
			{
				if (i == bfr_len - 1)
				{
					i++;
					break;
				}
				if (!sp(str[i + 1]))
				{
					space_end(&nbidx, &i, str_bfr, str);
					break;
				}
				i++;
			}
		}
		else
		{
			str_bfr[nbidx] = str[i];
			nbidx++;
			i++;
		}
	}
	str_bfr[_strlen(str_bfr)] = '\0';
	return (str_bfr);
}


