#include "shell.h"

/**
 * free_list - Free memory allocated to path holder
 * @head: List head
 * Return: Nothing
 */
void free_list(path_typ *head)
{
	path_typ *tmp = head;
	path_typ *sec;

	if (head)
	{
		while (tmp->next)
		{
			sec = tmp;
			tmp = tmp->next;
			free(sec->s);
			free(sec);
		}

		free(tmp->s);
		free(tmp);
	}
}

/**
 * free_arr_o_arr - Free space allocated to an array of arrays
 * @bfr: Array of arrays
 * Return: Nothing
 */
void free_arr_o_arr(char **bfr)
{
	int i;

	if (bfr != NULL)
	{
		for (i = 0; bfr[i] ; i++)
			free(bfr[i]);
		free(bfr);
	}
}

/**
 * _atoi - Cast string to integer
 * @str: String to convert
 * Return: Converted int
 */
int _atoi(char *str)
{
	unsigned int count = 0, size = 0;
	unsigned int io = 0, np = 1, m = 1, i;

	while (str[count] != '\0')
	{
		if (size > 0 && (str[count] < '0' || str[count] > '9'))
			break;

		if (str[count] == '-')
			np *= -1;

		if ((str[count] >= '0') && (str[count] <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		io = io + ((str[i] - 48) * m);
		m /= 10;
	}
	return (io * np);
}

/**
 * _itoa - Cast integer to string
 * @i: type int number
 * Return: String.
 */
char *_itoa(int i)
{
	unsigned int n;
	int len = num_len(i);
	char *bfr;

	bfr = malloc(sizeof(char) * (len + 1));
	if (bfr == 0)
		return (NULL);

	bfr[len] = '\0';

	if (i < 0)
	{
		n = i * -1;
		bfr[0] = '-';
	}
	else
	{
		n = i;
	}

	len--;
	do {
		bfr[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	while (n > 0)
		;
	return (bfr);
}

/**
 * num_len - Calculate the length of an int
 * @i: Number to check
 * Return: Number length
 */
int num_len(int i)
{
	unsigned int n;
	int len = 1;

	if (i < 0)
	{
		len++;
		n = i * -1;
	}
	else
	{
		n = i;
	}
	while (n > 9)
	{
		len++;
		n = n / 10;
	}

	return (len);
}
