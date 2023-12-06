#include "shell.h"

/**
 * _memcpy - function that copies memory area
 * @newptr: pointer to the memory area to copy
 * @ptr: pointer to the memory area to copy from
 * @size: size of the memory to copy
 * Return: pointer to the memory area newptr
 */

void *_memcpy(void *newptr, const void *ptr, size_t size)
{
	char *p = newptr;
	const char *q = ptr;

	while (size--)
		*p++ = *q++;
	return (newptr);
}

/**
 * _realloc - function that reallocates a memory block using malloc and free
 * @ptr: pointer to the memory previously allocated
 * @old_size: size, in bytes, of the allocated space for ptr
 * @new_size: new size, in bytes of the new memory block
 * Return: pointer to the new memory block
 */

void* _realloc(void* ptr, unsigned int old_size, unsigned int new_size)
{
	void* newptr;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		newptr = malloc(new_size);
		if (newptr == NULL)
			return (NULL);
		free(ptr);
		return (newptr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (new_size > old_size)
		_memcpy(newptr, ptr, old_size);
	free(ptr);
	return (newptr);
}