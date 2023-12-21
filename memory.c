#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
/* free a pointer and NULL the address */
	if (ptr && *ptr)
	{
		free(*ptr); /* free the pointer */
		*ptr = NULL; /* NULL the address */
		return (1); /* return success */
	}
	return (0);
}
