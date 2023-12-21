#include "shell.h"

/**
 * *_strncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 *
 * Return: the copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j; /* i is the index of dest, j is the index of src */
	char *s = dest; /* s is the pointer to dest */

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i]; /* copy the string */
		i++; /* increment the index */
	}
	if (i < n)
	{
		j = i; /* j is the index of src */
		while (j < n)
		{
			dest[j] = '\0'; /* fill the rest of the string with null */
			j++; /* increment the index */
		}
	}
	return (s);
}

/**
 * *_strncat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0; /* i is the index of dest */
	j = 0; /* j is the index of src */
	while (dest[i] != '\0')
		i++; /* increment the index */
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n) /* if the length of src is less than n */
		dest[i] = '\0';
	return (s); /* return the pointer to dest */
}

/**
 * *_strchr - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: the pointer to the first occurrence of c in s
 *        or NULL if not found
 */
char *_strchr(char *s, char c)
{
	do { /* do while loop to check the first character */
		if (*s == c)
			return (s);
	} while (*s++ != '\0'); /* increment the pointer */

	return (NULL);
}
