#include "shell.h"

/**
* _strlen - length of string
* @str: argument
*
* Return: length
*/

size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len])
		len++;

	return (len);
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
 * _strcmp - compares two strings
 * @s1: first string to compare
 * @s2: second string to compare
 *
 * Return: difference between strings
*/

int _strcmp(char *s1, char *s2)
{
	int i, len1, len2;

	len1 = _strlen(s1);
	len2 = _strlen(s2);

	if (len1 != len2)
		return (len1 - len2);

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i]);
	}

	return (0);
}