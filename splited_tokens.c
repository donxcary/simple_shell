#include "shell.h"

/**
 * _splitstring - int function
 * @str: argument
 * @delim: delimiter
 * Return: int
 */
 
int _splitstring(char* str, char* delim)
{
	int i = 0, num = 0;

	while (str[i])
	{
		if (str[i] == *delim)
			num++;
		i++;
	}
	return (num);
}

/**
 * split - split input to tokens
 * @buffer: string	
 * @delim: delimiter
 * Return: array of tokens
 */

char **split(char *buffer, char *delim)
{
	char **tokens;
	char *token;
	int i = 0, j = 0, num = 0;

	num = _splitstring(buffer, delim);
	tokens = malloc(sizeof(char *) * (num + 1));
	if (tokens == NULL)
		return (NULL);
	token = strtok(buffer, delim);
	while (token != NULL)
	{
		tokens[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (tokens[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(tokens[j]);
			free(tokens);
			return (NULL);
		}
		_strcpy(tokens[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
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
	char *token;
	int i = 0;

	if (str == NULL)
		str = save;
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
 * _strpbrk - int function
 * @s: char pointer
 * @accept: char pointer
 * Return: char pointer
 */

char *_strpbrk(char *s, char *accept)
{
	int i = 0, j = 0;

	while (s[i])
	{
		while (accept[j])
		{
			if (s[i] == accept[j])
				return (s + i);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}