#include "shell.h"

/**
 * *_memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 *
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	/* unsigned int is better than int */
	unsigned int i;
/* loop through the array and set each element to b */
	for (i = 0; i < n; i++)
		s[i] = b; /* set each element to b */
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 *
 * Return: void
 */
void ffree(char **pp)
{
/* create a copy of the pointer to the pointer */
	char **a = pp;

	if (!pp) /* if the pointer is null */
		return;
	while (*pp) /* while the pointer is not null */
		free(*pp++);
	free(a); /* free the pointer to the pointer */
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	/* create a pointer to a char */
	char *p;

	/* if the new size is the same as the old size */
	if (!ptr)
		return (malloc(new_size));
	if (!new_size) /* if the new size is 0 */
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr); /* return the pointer */

	p = malloc(new_size);
	if (!p) /* if the pointer is null */
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr); /* free the pointer */
	return (p);
}
