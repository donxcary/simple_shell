#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	/*copies a string*/
	int i = 0;

	/*while the source is not null*/
	if (dest == src || src == 0)
		return (dest); /*return the destination*/
	while (src[i])
	{
		dest[i] = src[i];
		i++; /*increment the index*/
	}
	dest[i] = 0; /*null terminate the destination*/
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	/*duplicates a string*/
	int length = 0; /*the length of the string*/
	char *ret; /*the return string*/

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++; /*get the length of the string*/
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str; /*copy the string*/
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++; /*increment the index*/
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0; /*reset the index*/
	}
	if (c != BUF_FLUSH)
		buf[i++] = c; /*add the character to the buffer*/
	return (1);
}
