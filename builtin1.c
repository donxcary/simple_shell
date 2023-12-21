#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *        with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	/* TODO: add -c, -d, -a, -w, -r, -n, -p, -s, -t, -u, -w */
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c; /* pointer to =, char at = */
	int ret; /* return value */

	p = _strchr(str, '=');
	if (!p)
		return (1); /* no = */
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c; /* restore = */
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p; /* pointer to = */

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p) /* no value */
		return (unset_alias(info, str));

	unset_alias(info, str); /* remove old alias */
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node) /* if node exists */
	{
		/* print alias */
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a); /* print alias name */
		_putchar('\''); /* print ' */
		_puts(p + 1); /* print alias value */
		_puts("'\n");
		return (0);
	}
	return (1); /* node doesn't exist */
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0; /* index */
	char *p = NULL; /* pointer to = */
	list_t *node = NULL; /* alias node */

	if (info->argc == 1)
	{
		node = info->alias; /* set node to alias head */
		while (node)
		{
			print_alias(node); /* print alias */
			node = node->next; /* go to next alias */
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		/* if argv[i] is an alias */
		p = _strchr(info->argv[i], '='); /* set p to = */
		if (p)
			set_alias(info, info->argv[i]); /* set alias */
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
