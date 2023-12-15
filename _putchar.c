#include "shell.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strlen - returns the length of a string
 * @s: string to check length
 *
 * Return: length of string
*/

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return (i);
}

/**
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: 0 if strings are equal, otherwise -1
*/

int _strcmp(char *s1, char *s2)
{
	int i;

	for (i = 0; s1[i] != 0 && s2[i] != 0; i++)
	{
		if (s1[i] != s2[i])
			return (-1);
	}

	return (0);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
*/

char *_strdup(char *str)
{
	char *dup;
	int i, len;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	dup = malloc(sizeof(char) * (len + 1));

	if (dup == NULL)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = str[i];

	dup[len] = '\0';

	return (dup);
}

/**
 * _strcat - concatenates two strings
 * @dest: string to append to
 * @src: string to append
 *
 * Return: pointer to concatenated string
*/

char *_strcat(char *dest, char *src)
{
	int i, j, len1, len2;
	char *new;

	len1 = _strlen(dest);
	len2 = _strlen(src);

	new = malloc(sizeof(char) * (len1 + len2 + 1));

	if (new == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
		new[i] = dest[i];

	for (j = 0; j < len2; j++)
		new[i + j] = src[j];

	new[i + j] = '\0';

	return (new);
}

/**
 * _strtok - tokenizes a string
 * @str: string to tokenize
 * @delim: delimiter to tokenize string by
 *
 * Return: pointer to tokenized string
*/

char *_strtok(char *str, char *delim)
{
	static char *token;
	int i, j, len;

	if (str != NULL)
		token = str;

	len = _strlen(token);

	for (i = 0; token[i] != '\0'; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (token[i] == delim[j])
			{
				token[i] = '\0';
				token = token + i + 1;
				return (token - i - 1);
			}
		}
	}

	token = token + len + 1;

	return (token - len - 1);
}

/**
 * _puts - prints a string
 * @str: string to print
 *
 * Return: void
*/

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);

	_putchar('\n');
}
