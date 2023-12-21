#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	/* print the environment */
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	/* get the value of an environment variable */
	list_t *node = info->env; /* pointer to the head of the list */
	char *p; /* pointer to the first occurence of '=' */

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p); /* return the value */
		node = node->next; /* move to the next node */
	}
	return (NULL); /* return NULL if not found */
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		/* if the number of arguments is not 3 */
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0); /* if successful */
	return (1);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int i; /* iterator */

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]); /* remove the variable */

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL; /* pointer to the head of the list */
	size_t i; /* iterator */

	for (i = 0; environ[i]; i++) /* loop through the environment */
		add_node_end(&node, environ[i], 0); /* add node to the end of the list */
	info->env = node; /* set the head of the list */
	return (0);
}
