#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0; /* bytes read */
	size_t len_p = 0; /* getline() buffer size */

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf); /* free the buffer */
		*buf = NULL; /* set to NULL */
		signal(SIGINT, sigintHandler);
#if USE_GETLINE /* use getline() */
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{/* if we read something */
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--; /* decrement length */
			}
			info->linecount_flag = 1; /* set linecount flag */
			remove_comments(*buf); /* remove comments */
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r; /* set length to bytes read */
				info->cmd_buf = buf; /* set cmd_buf to buffer */
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: length of input
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0; /* bytes read */
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* if we have a buffer */
	{
		j = i;
		p = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* set position to next command */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return bytes read */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0; /* bytes read */

	if (*i)
		return (0); /* if we have something in the buffer, return 0 */
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0) /* if we read something */
		*i = r; /* set length to bytes read */
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len; /* position and length */
	size_t k; /* length of string to copy */
	ssize_t r = 0, s = 0; /* bytes read and string length */
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr; /* set p to pointer to buffer */
	if (p && length)
		s = *length; /* set s to length of buffer */
	if (i == len)
		i = len = 0; /* reset position and length */

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1); /* EOF or nothing left to read */

	c = _strchr(buf + i, '\n'); /* find newline */
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* if realloc fails */
		return (p ? free(p), -1 : -1); /* free p and return -1 */

	if (s)
		_strncat(new_p, buf + i, k - i); /* copy string */
	else
		_strncpy(new_p, buf + i, k - i + 1); /* copy string */

	s += k - i; /* increment length */
	i = k; /* set position to next newline */
	p = new_p; /* set p to new_p */

	if (length)
		*length = s; /* set length to bytes read */
	*ptr = p; /* set ptr to p */
	return (s); /* return bytes read */
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n"); /* print newline */
	_puts("$ "); /* print prompt */
	_putchar(BUF_FLUSH); /* flush buffer */
}
