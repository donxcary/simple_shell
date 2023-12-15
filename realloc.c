#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i; /* unsigned int is used to compare with n */

	for (i = 0; i < n; i++) /* loop through the array */
		s[i] = b; /* set each element to the value of b */
	return (s); /* return the array */
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp; /* array of strings */

	if (!pp)
		return; /* if pp is NULL, return */
	while (*pp) /* loop through the array */
		free(*pp++); /* free each string */
	free(a); /* free the array */
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p; /* pointer to new block */

	if (!ptr)
		return (malloc(new_size)); /* malloc new_size bytes */
	if (!new_size)
		return (free(ptr), NULL); /* free ptr and return NULL */
	if (new_size == old_size)
		return (ptr); /* return ptr if new_size == old_size */

	p = malloc(new_size); /* malloc new_size bytes */
	if (!p)
		return (NULL); /* return NULL if malloc fails */

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--) /* loop through old_size */
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr); /* free ptr */
	return (p);
}