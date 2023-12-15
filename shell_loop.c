#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0; /* return value of get_input() */
	int builtin_ret = 0; /* return value of find_builtin() */

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info); /* clear info struct */
		if (interactive(info))
			_puts("$ "); /* print prompt */
		_eputchar(BUF_FLUSH); /* flush buffer */
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av); /* set info struct */
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);  /* find command */
		}
		else if (interactive(info))
			_putchar('\n'); /* print newline */
		free_info(info, 0); /* free info struct */
	}
	write_history(info); /* write history to file */
	free_info(info, 1);
	if (!interactive(info) && info->status) /* non-interactive mode */
		exit(info->status); /* exit with status */
	if (builtin_ret == -2) /* exit builtin */
		exit(info->status); /* exit with status */
	{
		if (info->err_num == -1) /* no error */
			exit(info->status);
		exit(info->err_num); /* exit with error number */
	}
	return (builtin_ret); /* return builtin return value */
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1; /* return value of builtin */

	/* builtin table */
	builtin_table builtintbl[] = {
		{"exit", _myexit}, /* exit builtin */
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++) /* find builtin */
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0) /* found */
		{
			info->line_count++; /* increment line count */
			built_in_ret = builtintbl[i].func(info); /* execute builtin */
			break; /* break out of loop */
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in the PATH
 * @info: the parameter & return info struct
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL; /* path to command */
	int i, k; /* index */

	info->path = info->argv[0]; /* set path to command */
	if (info->linecount_flag == 1)
	{
		info->line_count++; /* increment line count */
		info->linecount_flag = 0; /* reset linecount flag */
	}
	for (i = 0, k = 0; info->arg[i]; i++) /* check for delimiters */
		if (!is_delim(info->arg[i], " \t\n"))
			k++; /* increment k */
	if (!k)
		return; /* return if no command */

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path; /* set path to command */
		fork_cmd(info); /* fork command */
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127; /* set status to 127 */
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid; /* child process id */

	child_pid = fork(); /* fork a child process */
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:"); /* print error */
		return;
	}
	if (child_pid == 0) /* child process */
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{ 
			/* execute command */
			free_info(info, 1); /* free info struct */
			if (errno == EACCES)
				exit(126); /* exit with 126 */
			exit(1); /* exit with 1 */
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{/* parent process */
		wait(&(info->status)); /* wait for child process */
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status); /* get exit status */
			if (info->status == 126)
				print_error(info, "Permission denied\n"); /* print error */
		}
		else if (WIFSIGNALED(info->status))
		{
			info->status = WTERMSIG(info->status); /* get signal status */
			if (info->status == 2)
				print_error(info, "\n"); /* print error */
		}
	}
}