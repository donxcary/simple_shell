#include "shell.h"

/**
* _puts - prints the string
* @str: string
*/

void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
	_putchar('\n');
}

/**
* _memset - char function
* @s: prm
* @n: prm
* @b: prm
* Return: prm
*/

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
	{
		s[a] = b;
	}
	return (s);
}
