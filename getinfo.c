#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 *
 * Return: 0 on success, -1 on failure
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 *
 * Return: 0 on success, -1 on failure
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg) /* if arg is not NULL */
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL; /* for execve */
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			; /* count number of arguments */
		info->argc = i; /* set argc */

		replace_alias(info);
		replace_vars(info); /* replace $vars */
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 *
 * Return: 0 on success, -1 on failure
 */
void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg); /* free arg */
		if (info->env)
			free_list(&(info->env)); /* free env */
		if (info->history)
			free_list(&(info->history)); /* free history */
		if (info->alias)
			free_list(&(info->alias)); /* free alias */
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf); /* free cmd_buf */
		if (info->readfd > 2)
			close(info->readfd); /* close readfd */
		_putchar(BUF_FLUSH);
	}
}
