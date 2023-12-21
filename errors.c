#include "shell.h"

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0; /* index */

	if (!str) /* if str is NULL */
		return; /* do nothing */
	while (str[i] != '\0')
	{
		/* while str is not at the end */
		_eputchar(str[i]);
		i++; /* increment index */
	}
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 */
int _eputchar(char c)
{
	/* write to stderr */
	static int i;
	static char buf[WRITE_BUF_SIZE];

	/* static variables are initialized once */
	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; /* add char to buffer */
	return (1);
}

/**
 * _putfd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 */
int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0; /* reset index */
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; /* add char to buffer */
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str) /* if str is NULL */
		return (0);
	while (*str) /* while str is not at the end */
	{
		i += _putfd(*str++, fd); /* print char and increment index */
	}
	return (i);
}
