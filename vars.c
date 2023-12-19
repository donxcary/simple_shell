#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	/* check if current char is a chain delimeter */
	size_t j = *p; /* current position in buf */

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		/* printf("found ||\n"); */
		buf[j] = 0; /* replace || with null */
		j++; /* skip over second | */
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0); /* not a chain delimeter */
	*p = j; /* update current position in buf */
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	/* check if we should continue chaining */
	size_t j = *p; /* current position in buf */

	if (info->cmd_buf_type == CMD_AND)
	{
		/* if last command failed, skip over next command */
		if (info->status)
		{
			buf[i] = 0; /* replace & with null */
			j = len; /* skip over next command */
		}
	}
	if (info->cmd_buf_type == CMD_OR) /* if last command succeeded */
	{
		if (!info->status)
		{
			buf[i] = 0; /* replace | with null */
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Description: replaces an alias in the tokenized string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node; /* node in alias linked list */
	char *p; /* pointer to value of alias */

	for (i = 0; i < 10; i++)
	{
		/* check if first token is an alias */
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0); /* no alias found */
		free(info->argv[0]); /* free old command */
		p = _strchr(node->str, '='); /* get value of alias */
		if (!p) /* if no value */
			return (0);
		p = _strdup(p + 1); /* copy value of alias */
		if (!p)
			return (0);
		info->argv[0] = p; /* replace command with alias value */
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 * Description: replaces vars in the tokenized string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0; /* index of current token */
	list_t *node; /* node in env linked list */

	for (i = 0; info->argv[i]; i++) /* for each token */
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue; /* not a var */

		if (!_strcmp(info->argv[i], "$?"))
		{
			/* replace $? with exit status */
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$")) /* replace $$ with pid */
		{
			/* printf("found $$\n"); */
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0))); /* replace $$ with pid */
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup("")); /* replace with empty string */

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Description: replaces string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);  /* free old string */
	*old = new; /* replace with new string */
	return (1); /* replaced */
}

