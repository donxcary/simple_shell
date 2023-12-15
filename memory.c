#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
		/* if ptr is not NULL and *ptr is not NULL */
	{
		free(*ptr); /* free the memory */
		*ptr = NULL; /* NULL the address */
		return (1); /* return 1 for success */
	}
	return (0); /* return 0 for failure */
}
