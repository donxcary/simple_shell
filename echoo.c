#include "shell.h"


/**
* handle_env_var - handle environment variables
*
* @arg: argument
*
* Return: void
*/

void handle_env_var(char *arg)
{
	char *va_name, *va_value;

	va_name = arg + 1; /* skip $ */
	va_value = get_env(va_name);
	if (va_value != NULL)
	{
		_print_str(va_value);
		_print_str("\n");
	}
	else
		_print_str("\n");
}

/**
* _echoo - print a string
* @arg: argument
*
* Return: 0
*/
int _echoo(char **arg)
{
	int pid, last_exit_status = 0;
	char *s;
	size_t len;

	if (arg[1] == NULL)
	{
		_print_str("\n");
		return (0);
	}
	else
	{
		if (_strncmp("$$", arg[1], _strlen(arg[1])) == 0)
		{
			pid = getpid();
			_print_num(pid);
			_print_str("\n");
		}
		else if (_strncmp("$?", arg[1], _strlen(arg[1])) == 0)
		{
			_print_num(last_exit_status);
			_print_str("\n");
		}
		else if (arg[1][0] == '$')
			handle_env_var(arg[1]);
		else if ((arg[1][0] == '"' && arg[1][_strlen(arg[1]) - 1] == '"') ||
			(arg[1][0] == '\'' && arg[1][_strlen(arg[1]) - 1] == '\''))
		{
			s = arg[1] + 1;
			len = _strlen(arg[1]) - 2;
			s[len] = '\0';
			_print_str(s);
			_print_str("\n");
		}
		else
		{
			_print_str(arg[1]);
			_print_str("\n");
		}
	}
	return (0);
}