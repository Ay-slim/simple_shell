#include <unistd.h>

/**
 * _putchar - Prints a character to a given stream
 * @c: Char to print
 * @fd: Stream to print to
 * Return: Nothing
 */
void _putchar(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * _putstr - Prints a string to a given stream
 * @s: String to print
 * @fd: Stream to write to
 * Return: Nothing
 */
void _putstr(char *s, int fd)
{
	while (*s)
	{
		_putchar(*s, fd);
		s++;
	}
}

