#include "shell.h"

/**
* _strcpy - copies the content of the source string to destination string
* @dest: destination arguments
* @src: source arg
* Return: copy of string
*/
char *_strcpy(char *dest, const char *src)
{
	char *tmp = dest;

	while (*src != '\0')
	{
		*dest++ = *src++;
	}
	*dest = '\0';

	return (tmp);
}

/**
* _snprint - prints a string to stdout
* @str: string to print
* @size: size of string
* @format: format of string
* Return: number of characters printed
*/
int _snprint(char *str, size_t size, const char *format, ...)
{
va_list args;
	int i;
	char *tmp = str;

	va_start(args, format);
	i = vsnprintf(str, size, format, args);
	va_end(args);

	if (i < 0)
		return (-1);
	if (i >= (int)size)
	{
		str = malloc(sizeof(char) * (i + 1));
		if (!str)
			return (-1);
		va_start(args, format);
		i = vsnprintf(str, size, format, args);
		va_end(args);
		if (i < 0)
			return (-1);
		_strcpy(tmp, str);
		free(str);
		return (i);
	}
	return (i);
}

/**
* _strncpy - copies the content of the source to destination
* @dst: argument
* @src: argument
* @n: argument
* Return: copy of string
*/
char *_strncpy(char *dst, const char *src, size_t n)
{
	char *dst_c = dst;

	while (n > 0 && *src != '\0')
	{
		*dst++ = *src++;
		n--;
	}
	while (n > 0)
	{
		*dst++ = '\0';
		n--;
	}
	return (dst_c);
}
