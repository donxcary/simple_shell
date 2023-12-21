#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{ /* if we don't have a copy of our environ, or it's changed */
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
 /* return the copy of our environ */
	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @var: the string env var property
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p; /* pointer to the start of the string */

	if (!node || !var)
		return (0);

	while (node)
	{/* if the string starts with var, and the next char is '=' */
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{/* delete the node at index i */
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env; /* reset the node pointer */
			continue; /* continue to check for more matches */
		}
		node = node->next; /* move to the next node */
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Set an environment variable
 * @var: the string env var property
 * @value: the string env var value
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var); /* copy the var */
	_strcat(buf, "="); /* add the '=' */
	_strcat(buf, value); /* add the value */
	node = info->env; /* reset the node pointer */
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str); /* free the old string */
			node->str = buf; /* replace the string */
			info->env_changed = 1;
			return (0);
		}
		node = node->next; /* move to the next node */
	}
	add_node_end(&(info->env), buf, 0);
	free(buf); /* free the buffer */
	info->env_changed = 1;
	return (0);
}
