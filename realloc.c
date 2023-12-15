#include "shell.h"

/**
* _memcpy - copy infos between void ptrs
* @newptr: destination ptr
* @ptr: the source pointer
* @size: the size of the new ptr
* Return: 0
*/

void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_newptr = (char *)newptr;
	char *char_ptr = (char *)ptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
* _eputs - prints a string to stderr
* @str: the string to print
* Return: 0
*/
void _eputs(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	write(STDERR_FILENO, str, i);
}

/**
* _eputchar - prints a char to stderr
* @char: the char to print
* Return: 0
*/
int _eputchar(char)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
* _putfd - prints a char to a file descriptor
* @c: the char to print
* @fd: the file descriptor
* Return: 0
*/
int _putfd(char c, int fd)
{
	return (write(fd, &c, 1));
}

/**
* _putsfd - prints a string to a file descriptor
* @str: the string to print
* @fd: the file descriptor
* Return: 0
*/
int _putsfd(char *str, int fd)
{
int i;

	for (i = 0; str[i] != '\0'; i++)
		;
	return (write(fd, str, i));
}

/**
* _strcmp - compares two strings
* @s1: first string
* @s2: second string
* Return: 0 if equal, else the difference
*/
int _strcmp(char *s1, char *s2)
{
int i = 0;

	while (s1[i] == s2[i] && s1[i] != '\0')
		i++;

	return (s1[i] - s2[i]);
}

/**
* starts_with - checks if a string starts with another
* @str: the string to check
* @start: the string to check against
* Return: 0 if equal, else the difference
*/
char *starts_with(const char *str, const char *start)
{
int i = 0;

	while (str[i] == start[i] && str[i] != '\0')
		i++;

	if (start[i] == '\0')
		return (str + i);
	return (NULL);
}

/**
* _realloc - reallocates a memory block
* @ptr: pointer to the memory prev allocated
* @old_size: size in bytes of the allocated space of pointer
* @new_size: new size in bytes of the new memory block
* Return: pointer
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(newptr, ptr, new_size);
	else
		_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
* _atoi - converts a string to an integer
* @s: the string to convert
* Return: the integer
*/

int _atoi(char *s)
{
	int i, sign = 1, num = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		else if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + (s[i] - '0');
		else if (num > 0)
			break;
	}
	return (num * sign);
}