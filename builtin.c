#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: exits with a given exit status
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if there is an exit arguments */
	{
		exitcheck = _erratoi(info->argv[1]); /* check if it is a number */
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1; /* if no exit arguments, exit with status 0 */
	return (-2);
}

/**
* _getenv - gets the value of an environment variable
* @info: Structure containing potential arguments.
* @name: name of the environment variable
* Return: value of the environment variable
*/

int *_getenv(info_t *info, char *name)
{
	int i, j;

	for (i = 0; info->environ[i]; i++)
	{
		for (j = 0; name[j]; j++)
		{
			if (name[j] != info->environ[i][j])
				break;
		}
		if (name[j] == '\0')
			return (info->environ[i]);
	}
	return (NULL);
}

/**
 * _mycd - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int _mycd(info_t *info)
{
	int chdir_ret;

	if (/* some condition */)
	{
		/* some code */
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		/* some code */
	}
	else
	{
		chdir_ret = chdir(/* some path */);
		if (chdir_ret == -1)
		{
			/* handle error */
		}
		else
		{
			/* some code */
		}
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array; /* temp att_unused workaround */

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
