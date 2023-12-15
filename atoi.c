#include "shell.h"

/**
* _atoi - convert a string to an integer
* 
* @s: string to convert
* 
* Return: the integer value of the converted string
*/

int _atoi(char *s)
{
	unsigned int cmp = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + cmp) != '\0')
	{
		if (size > 0 && (*(s + cmp) < '0' || *(s + cmp) > '9'))
			break;

		if (*(s + cmp) == '-')
			pn *= -1;

		if ((*(s + cmp) >= '0') && (*(s + cmp) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		cmp++;
	}
	for (i = cmp - size; i < cmp; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}