#include "shell.h"

/**
 * child_call - Calls the child process for simple shell
 * @argv: Array of arg path and possibly options
 * Return: Nothing
 */
void child_call(char **argv)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("Exec failure");
			free_mult(argv);
			exit(1);
		}
		free_mult(argv);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * control_center - Processes the buffer from stdin and decides what to do
 * @buffer: Buffer from stdin
 * Return: 0 on failure, 1 if it works
 */
int control_center(char *buffer)
{
	char **argv = extract_term_args(buffer);

	if (argv == NULL)
		return (0);
	child_call(argv);
	return (1);
}

/**
 * mult_cmd - Handles multiple commands delimited by a ;
 * @buffer: Buffer from stdin
 * @symbol: Delimiting symbol
 * Return: Nothing
 */
void mult_cmd(char *buffer, char *symbol)
{
	char **cmds = _strtok(buffer, symbol);

	while (*cmds)
	{
		control_center(*cmds);
		cmds++;
	}
}

/**
 * shell_core - The core function for the simple shell project
 * Return: Nothing
 */
void shell_core(void)
{
	char *buffer;

	while (1)
	{
		buffer = malloc(1024 * sizeof(char));
		if (buffer == NULL)
			exit(1);
		if (isatty(STDIN_FILENO))
			_putstr("$ ", 1);
		fflush(stdout);
		if (read(STDIN_FILENO, buffer, 1024) < 1)
		{
			exit(0);
		}
		if (_strincludes(buffer, ';'))
		{
			mult_cmd(buffer, " ; ");
			continue;
		}
		if (_strlen(buffer) > 1 && _strincludesstr(buffer, "&&"))
		{
			mult_cmd(buffer, " && ");
			continue;
		}
		if (mid_newline(buffer))
		{
			mult_cmd(buffer, "\n");
			continue;
		}
		if (!control_center(buffer))
			continue;
		free(buffer);
	}
}

/**
 * main - The main calling function for the simple shell project
 * Return: Nothing
 */
int main(void)
{
	shell_core();
	return (0);
}

