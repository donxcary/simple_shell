#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int i = 0; /* length counter */

	if (!s) /* if s is NULL */
		return (0);

	while (*s++) /* while the current char is not null */
		i++; /* increment counter */
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	/* while s1 and s2 are not at null byte */
	while (*s1 && *s2)
	{
		if (*s1 != *s2) /* if the chars are not equal */
			return (*s1 - *s2); /* return the difference */
		s1++; /* increment s1 */
		s2++; /* increment s2 */
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL); /* not a match */
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++; /* move to end of dest */
	while (*src)
		*dest++ = *src++;
	*dest = *src; /* copy null byte */
	return (ret);
}
