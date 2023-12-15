#include "shell.h"

/**
* _splitPATH - int function
* @str: prm
* Return: num Path
*/

int _splitPATH(char *str)
{
	int a;
	int count = 0;
	int srcflg = 1;

	for (a = 0; str[a]; a++)
	{
		if (str[a] != ':' && srcflg == 1)
		{
			count += 1;
			srcflg = 0;
		}
		if (str[a + 1] == ':')
		{
			srcflg = 1;
		}
	}
	return (count);
}

/**
* _PATHstrcmp - int function
* @s1: prm
* @s2: prm
* Return: zero
*/

int _PATHstrcmp(const char *s1, const char *s2)
{
	int a;

	for (a = 0; s2[a] != '='; a++)
	{
		if (s1[a] != s2[a])
			return (-1);
	}
	return (0);
}

/**
* _con_cat - charcter function
* @arg: vrbl
* @tok: vrbl
* @tmp: vrbl
* Return: zero
*/

char *_con_cat(char *tmp, char **arg, char *tok)
{
	int len = 0;

	_memset(tmp, 0, 256);
	len = _strlen(tok) + _strlen(arg[0]) + 2;
	_strcat(tmp, tok);
	_strcat(tmp, "/");
	_strcat(tmp, arg[0]);
	tmp[len - 1] = '\0';
	return (tmp);
}
