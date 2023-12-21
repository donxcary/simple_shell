#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
/* determines if a file is an executable command */
	struct stat st;

/* stat() stats the file pointed to by path and fills in buf */
	(void)info; /* unused parameter */
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1); /* file exists */
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
/* duplicates characters */
	static char buf[1024];
	int i = 0, k = 0; /* i = index, k = counter */

/* copy characters from pathstr to buf */
	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0; /* null terminate buf */
	return (buf);
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
	/* if cmd starts with ./ */
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
	/* loop through pathstr */
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path) /* if path is empty */
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/"); /* concatenate path and cmd */
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break; /* break if end of pathstr */
			curr_pos = i;
		}
		i++; /* increment index */
	}
	return (NULL);
}
