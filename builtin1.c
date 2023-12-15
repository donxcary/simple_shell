#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line,
 * preceded with line numbers, starting at 0.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history); /* print history */
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: parameter
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * print_alias - prints alias
 * @node: node to print
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p;

	if (!node)
		return (1);
	p = _strchr(node->str, '=');
	*p = 0;
	_puts(node->str);
	_puts("='");
	_puts(++p);
	_puts("'\n");
	*p = '=';
	return (0);
}

/**
 * set_alias - sets alias
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
