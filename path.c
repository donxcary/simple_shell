#include "shell.h"

/**
 * _splitPATH - int function
 * @str: char pointer
 * Return: num PATH
 */

int _splitPATH(char* str)
{
	int i = 0, num = 0;

	while (str[i])
	{
		if (str[i] == ':')
			num++;
		i++;
	}
	return (num);
}

/**
 * _strtok - int function
 * @str: char pointer
 * @delim: char pointer
 * Return: char pointer
 */

char *_strtok(char *str, char *delim)
{
	static char *save;
	char *token = NULL;

	if (str == NULL)
		str = save;
	str += _strspn(str, delim);
	if (*str == '\0')
		return (NULL);
	token = str;
	str = _strpbrk(token, delim);
	if (str == NULL)
		save = _strchr(token, '\0');
	else
	{
		*str = '\0';
		save = str + 1;
	}
	return (token);
}

/**
 * _PATHstrcmpr - int function
 * @s1: char pointer
 * @s2: char pointer
 * Return: int
 */

int _PATHstrcmpr(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break;
		i++;
	}
	if (s1[i] == '=' && s2[i] == '\0')
		return (0);
	return (1);
}

/**
 * _PATH - int function
 * @args: char pointer
 * @PATH: char pointer
 * @copy: char pointer
 * Return: char pointer
 */

char *_PATH(char **args, char *PATH, char *copy)
{
	char *ptr = NULL;
	char *token = NULL;
	int i = 0;

	token = _strtok(PATH, ":");
	while (token != NULL)
	{
		ptr = malloc(sizeof(char) * (_strlen(token) + _strlen(args[0]) + 2));
		if (ptr == NULL)
			return (NULL);
		while (token[i])
		{
			ptr[i] = token[i];
			i++;
		}
		ptr[i] = '/';
		i++;
		ptr[i] = '\0';
		ptr = _strcat(ptr, args[0]);
		if (access(ptr, F_OK) == 0)
		{
			free(copy);
			return (ptr);
		}
		free(ptr);
		token = _strtok(NULL, ":");
		i = 0;
	}
	free(copy);
	return (NULL);
}