#include "shell.h"

/**
* _strcat - concatenates 2 strings
* @dstn: the destination of the buffer
* @src: the source of the buffer
* Return: the pointer to the destionation of the buffer
*/

char *_strcat(char *dstn, char *src)
{
	int a;
	int b;

	for (a = 0; dstn[a] != '\0'; a++)
		;
	for (b = 0; src[b] != '\0'; b++, a++)
		dstn[a] = src[b];
	dstn[a] = '\0';
	return (dstn);
}
