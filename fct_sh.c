#include "shell.h"
/**
* _read - function
* Return: char
*/
char *_read(void)
{
	int i = 0;
	ssize_t count = 0;
	size_t n = 0;
	char *buff = NULL;

	count = get_line(&buff, &n, stdin);
	if (count == -1)
	{
		free(buff);
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (buff[count - 1] == '\n' || buff[count - 1] == '\t')
		buff[count - 1] = '\0';
	for (i = 0; buff[i]; i++)
	{
		if (buff[i] == '#' && buff[i - 1] == ' ')
		{
			buff[i] = '\0';
			break;
		}
	}
	return (buff);
}

/**
* checks - function
* @arg: char
* @buff: char
* @exitstat: int
* Return: char
*/
int checks(char **arg, char *buff, int exitstat)
{
	int n;

	if (_strncmp(arg[0], "env", 3) == 0)
	{
		_env();
		for (n = 0; arg[n]; n++)
			free(arg[n]);
		free(arg);
		free(buff);
		return (1);
	}
	else if (_strncmp(arg[0], "exit", 4) == 0)
	{
		if (arg[1] != NULL)
			exitstat = atoi(arg[1]);
		for (n = 0; arg[n]; n++)
			free(arg[n]);
		free(arg);
		free(buff);
		exit(exitstat);
	}
	else if (_strncmp(arg[0], "echo", 4) == 0)
	{
		_echoo(arg);
		for (n = 0; arg[n]; n++)
			free(arg[n]);
		free(arg);
		free(buff);
		return (1);
	}
	else

	return (0);

}
