#include "shell.h"

/**
 * space_end - Handles condition when space is done
 * @nbidx: Pointer to nbidx
 * @i: Pointer to i
 * @str_bfr: new string buffer
 * @str: old string buffer
 * Return: void
 */
void space_end(unsigned int *nbidx, unsigned int *i, char *str_bfr, char *str)
{
	if (*nbidx > 0)
	{
		str_bfr[*nbidx] = ' ';
		*i = *i + 1;
		*nbidx = *nbidx + 1;
	}
	else
	{
		str_bfr[*nbidx] = str[*i + 1];
		*i = *i + 2;
		*nbidx = *nbidx + 1;
	}
}

/**
 * mid_newline - Checks if there's a /n char in the middle of the string
 * @bfr: Buffer to check
 * Return: 1 if mid new line. 0 if no mid new line
*/
int mid_newline(char *bfr)
{
	unsigned int len = _strlen(bfr);
	unsigned int i = 0;

	if (!_strincludes(bfr, '\n'))
		return (0);
	while (i < len)
	{
		if (bfr[i] == '\n' && bfr[i + 1])
			return (1);
		i++;
	}
	return (0);
}

