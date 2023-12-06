#include "shell.h"

/**
 * _puts - print a string
 * @str: string to print
 * Return: 0 on success
 */

int _puts(char *str)
{
	int i = 0;

	while (str[i])
	{
		_putchar(str[i]);
		i++;
	}
	return (0);
}

/**
 * _putchar - print a character
 * @c: character to print
 * Return: 0 on success
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - return the length of a string
 * @s: string to check
 * Return: length of a string
 */

int _strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

/**
 * _strcat - concatenate two strings
 * @dest: string to concatenate
 * @src: string to concatenate
 * Return: pointer to the resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0, len = 0;
	char *ptr = NULL;

	len = _strlen(dest) + _strlen(src);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	while (dest[i])
	{
		ptr[i] = dest[i];
		i++;
	}
	while (src[j])
	{
		ptr[i] = src[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/**
 * _memset - fill memory with a constant byte
 * @s: memory area to fill	
 * @b: constant byte
 * @n: number of bytes to fill
 * Return: pointer to the memory area s
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}