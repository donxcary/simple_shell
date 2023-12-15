#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st; /* struct to hold file info */

	(void)info;
	if (!path || stat(path, &st)) /* get file info */
		return (0); /* file does not exist */

	if (st.st_mode & S_IFREG)
	{
		return (1); /* file exists and is a regular file */
	}
	return (0); /* file exists but is not a regular file */
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024]; /* static buffer to hold path */
	int i = 0, k = 0; /* iterators */

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':') /* skip colons */
			buf[k++] = pathstr[i];
	buf[k] = 0; /* null terminate */
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL); /* no PATH variable */
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i); /* duplicate chars */
			if (!*path)
				_strcat(path, cmd); /* no path, use cmd */
			else
			{
				_strcat(path, "/"); /* add slash */
				_strcat(path, cmd); /* add cmd */
			}
			if (is_cmd(info, path))
				return (path); /* found cmd */
			if (!pathstr[i])
				break; /* end of string */
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * find_cmd - finds the full path of a cmd
 * @info: the info struct
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */

char *find_cmd(info_t *info, char *cmd)
{
	char *pathstr = NULL, *path = NULL; /* PATH string and path */

	if (!cmd)
		return (NULL);
	if (cmd[0] == '/')
	{
		if (is_cmd(info, cmd)) /* check if cmd is a file */
			return (cmd);
	}
	else
	{
		pathstr = _getenv(info->env, "PATH"); /* get PATH string */
		path = find_path(info, pathstr, cmd); /* find cmd in PATH */
		if (path)
			return (path);
	}
	return (NULL);
}

/**
 * loophsh - loops the shell
 * @av: the argument vector
 * Return: 0 on success
 */
int loophsh(char **av)
{
	info_t info; /* struct to hold shell info */
	char *line = NULL, **args = NULL, *cmd = NULL; /* cmd and args */
	int status = 0, i = 0; /* status of last command */

	(void)av;
	init_info(&info);
	while (1)
	{
		if (isatty(STDIN_FILENO)) /* if stdin is a terminal */
			write(STDOUT_FILENO, "$ ", 2); /* print prompt */
		line = _getline(&info);
		if (!line)
			break; /* user pressed ctrl+d */
		args = split_line(line);
		if (!args)
			continue; /* user pressed enter */
		if (!args[0])
		{
			free(args);
			continue; /* user pressed enter */
		}
		cmd = find_cmd(&info, args[0]); /* find cmd */
		if (!cmd) /* cmd not found */
		{
			print_error(&info, args[0], "not found");
			free(args);
			continue;
		}
		status = execute_cmd(&info, cmd, args);
		for (i = 0; args[i]; i++)
			free(args[i]);
		free(args); /* free args */
		if (status == 2)
			break; /* user typed exit */
	}
	free_info(&info); /* free info */
	return (0); /* exit */
}