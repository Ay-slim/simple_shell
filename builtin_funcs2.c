#include "shell.h"

/**
 * _putnum - Print a number
 * @num: Number to pring
 * Return: Nothing
 */
void _putnum(int num)
{
	while (1)
	{
		_putchar(((num % 10) + '0'), 1);
		if (!(num / 10))
			break;
		num /= 10;
	}
	_putchar('\n', 1);
}

/**
 * _exitstatus - Return exit status
 * Return: Nothing
 */
void _exitstatus(void)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		exit(1);
	}
	else if (pid == 0)
	{
		exit(1);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			_putnum(WIFEXITED(status));
		}
	}
}
/**
 * _echo - Handles the echo builtin command
 * @argv: Array of strings containing args
 * Return: Nothing
 */
void _echo(char **argv)
{
	unsigned int argc = _strarrlen(argv);
	env_typ_t env_deets;
	pid_t proc_id;
	char *env_name;

	if (argc > 1 && argv[1][0] == '$')
	{
		if (argv[1][1] == '$')
		{
			proc_id = getpid();
			_putnum(proc_id);
			return;
		}
		else if (argv[1][1] == '?')
		{
			_exitstatus();
			return;
		}
		else
		{
			env_name = _substr(argv[1], 1, _strlen(argv[1]));
			env_deets = _genv_max(env_name);
			if (env_deets.val)
				_putstr(env_deets.val, 1);
			_putchar('\n', 1);
			return;
		}
	}
	if (argv[1])
		_putstr(argv[1], 1);
	_putchar('\n', 1);
}

