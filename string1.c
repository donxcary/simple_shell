#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0; /* counter */
	if (dest == src || src == 0)
		return (dest); /* account for NULL */
	while (src[i])
	{
		dest[i] = src[i]; /* copy string */
		i++; /* increment counter */
	}
	dest[i] = 0; /* null terminate */
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	/* duplicate a string */
	int length = 0; /* length of string */
	char *ret; /* return value */

	if (str == NULL)
		return (NULL); /* account for NULL */
	while (*str++)
		length++; /* get length of string */
	ret = malloc(sizeof(char) * (length + 1)); /* allocate memory */
	if (!ret)
		return (NULL); /* account for malloc failure */
	for (length++; length--;)
		ret[length] = *--str; /* copy string */
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0; /* counter */
	if (!str)
		return; /* account for NULL */
	while (str[i] != '\0')
	{
		_putchar(str[i]); /* print string */
		i++; /* increment counter */
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1, on error -1
 */
int _putchar(char c)
{
	/* write a character */
	static int i; /* index */
	static char buf[WRITE_BUF_SIZE]; /* buffer */

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i); /* write buffer */
		i = 0; /* reset index */
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; /* add character to buffer */
	return (1);
}