#include "shell.h"

/**
 * _getenv - gets the value of an environment variable	
 * @name: name of the environment variable
 *	Return: value of the environment variable
 */

char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char *value = NULL;

	if (name == NULL)
		return (NULL);

	while (environ[i] != NULL)
	{
		while (environ[i][j] == name[j])
		{
			if (environ[i][j + 1] == '=')
			{
				value = malloc(sizeof(char) * 1024);
				if (value == NULL)
					return (NULL);
				while (environ[i][j + 2 + k] != '\0')
				{
					value[k] = environ[i][j + 2 + k];
					k++;
				}
				value[k] = '\0';
				return (value);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}

/**
 * _setenv - sets the value of an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * Return: 0 on success, -1 on failure
 */

int _setenv(const char *name, const char *value)
{
	int i = 0, j = 0, k = 0;
	char *newenv = NULL;

	if (name == NULL || value == NULL)
		return (-1);

	while (environ[i] != NULL)
	{
		while (environ[i][j] == name[j])
		{
			if (environ[i][j + 1] == '=')
			{
				newenv = malloc(sizeof(char) * 1024);
				if (newenv == NULL)
					return (-1);
				while (environ[i][j + 2 + k] != '\0')
				{
					newenv[k] = environ[i][j + 2 + k];
					k++;
				}
				newenv[k] = '\0';
				free(environ[i]);
				environ[i] = malloc(sizeof(char) * 1024);
				if (environ[i] == NULL)
					return (-1);
				environ[i] = _strcat((char *)name, "=");
				environ[i] = _strcat(environ[i], (char *)value);
				return (0);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (-1);
}