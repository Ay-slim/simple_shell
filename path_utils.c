#include "shell.h"

/**
 * _readcmd - Reads commands from stdin
 * @inp_struct: Data passed to shell
 * @bfr: Holds user input
 * @n: Buffer size
 * Return: Tokenized commands
 */
char **_readcmd(inp_typ *inp_struct, char *bfr, size_t n)
{
	char **arr = NULL;
	char *token;
	size_t k = 0;
	ssize_t i, r;

	r = _getline(&bfr, &n, stdin);
	if (r == -1)
	{
		free(bfr);
		inp_struct->interact = 3;
		return (arr);
	}
	r = _stripcmt(&bfr);
	if (r == 0)
		return (NULL);
	for (i = 0; i < r; i++)
	{
		if (bfr[i] == ' ' || bfr[i] == '\n' || bfr[i] == '\t' ||
				bfr[i] == '\r' || bfr[i] == '\a')
		{
			k++;
		}
		else
			continue;
	}
	arr = malloc(sizeof(char *) * (k + 1));
	token = _strtok(bfr, DELIM_T);
	i = 0;
	while (token != NULL)
	{
		arr[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		_strcpy(arr[i], token);
		token = _strtok(NULL, DELIM_T);
		i++;
	}
	arr[i] = NULL;
	free(bfr);
	return (arr);
}

/**
 * _stripcmt - Removes comments
 * @bfr: String from stdin
 * Return: Length of buffer less comments
 */
int _stripcmt(char **bfr)
{
	int m = 0, i, j = 0;
	char *buf = _strdup(*bfr);
	char *tmp = NULL, prev = 'c';

	for (; buf[m] != '\0'; m++)
	{
		if (m == 0 && buf[m] == '#')
		{
			free(buf);
			return (0);
		}
		if (j == 0 && buf[m] == '#')
		{
			free(buf);
			return (0);
		}
		if (buf[m] != ' ' && buf[m] != '\t')
			j++;
		if (prev == ' ' && buf[m] == '#')
			break;

		prev = buf[m];
	}
	if (m == _strlen(*bfr))
	{
		free(buf);
		return (m);
	}
	tmp = malloc(sizeof(char) * (m + 2));
	for (i = 0; buf[i] != '#'; i++)
		tmp[i] = buf[i];
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	free(*bfr);
	*bfr = tmp;
	free(buf);

	return (m + 1);
}

/**
 * _putline - Feeds buffer into line pointer
 * @ln: Getline address
 * @bfr: Read call data
 * @n: Line size
 * @len: Buffer length
 * Return: Nothing
 */
void _putline(char **ln, size_t *n, char *bfr, size_t len)
{
	if (*ln == NULL || *n < len)
	{
		if (len > BUFSIZE)
			*n = len;
		else
			*n = BUFSIZE;
		*ln = bfr;
	}
	else
	{
		_strcpy(*ln, bfr);
		free(bfr);
	}
}

/**
 * _getline - Read user input from stdin
 * @bfr: Buffer pointer
 * @n: Buffer size pointer
 * @riv: Stream file descriptor
 * Return: Buffer size
 */
ssize_t _getline(char **bfr, size_t *n, FILE *riv)
{
	int fd;
	char *buf, c = 'c';
	static ssize_t input;
	ssize_t r;
	size_t size;

	buf = malloc(sizeof(char) * BUFSIZE);
	if (!buf)
		return (-1);

	fd = fileno(riv);
	while (c != NEWLINE)
	{
		r = read(fd, &c, 1);
		if ((r == 0 && input == 0) || r == -1)
		{
			free(buf);
			return (-1);
		}
		if (r == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
		{
			buf = _realloc(buf, input, input + 1);
		}
		buf[input] = c;
		input++;
	}
	buf[input] = '\0';
	_putline(bfr, n, buf, input);
	size = input;
	if (r != 0)
		input = 0;
	return (size);
}

