#include "shell.h"

/**
* _strdup - function duplicates string
* @s: string
* Return: duplicated string
*/

char *_strdup(const char *s)
{
	char *d;
	size_t i, len;

	if (s == NULL)
		return (NULL);
	len = _strlen(s);
	d = malloc((len + 1) * sizeof(char));

	if (d == NULL)
		return (NULL);
	for (i = 0; i < len; i++)
		d[i] = s[i];

	d[len] = '\0';

	return (d);
}
