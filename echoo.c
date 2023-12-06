#include "shell.h"

/**
* handle_enr_var - handle enviroment variables
* @str: string to handle
* Return: string with enviroment variables
*/

char *handle_enr_var(char *str)
{
	char *new_str = NULL, *aux = NULL, *aux2 = NULL;
	int i = 0, j = 0, k = 0, len = 0, len2 = 0;

	if (str == NULL)
		return (NULL);
	len = _strlen(str);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			aux = _getenv("PATH");
			len2 = _strlen(aux);
			aux2 = malloc(sizeof(char) * (len2 + 1));
			if (aux2 == NULL)
				return (NULL);
			while (aux[j])
			{
				aux2[j] = aux[j];
				j++;
			}
			aux2[j] = '\0';
			free(aux);
			while (aux2[k])
			{
				new_str[k] = aux2[k];
				k++;
			}
			free(aux2);
		}
		else
			new_str[k] = str[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	return (new_str);
}

/**
* _echo - print a string
* @args: arguments
* Return: 0 on success
*/

int _echo(char **args)
{
	int i = 1, j = 0, len = 0;
	char *new_str = NULL;

	while (args[i])
	{
		new_str = handle_enr_var(args[i]);
		if (new_str == NULL)
			return (0);
		len = _strlen(new_str);
		while (new_str[j])
		{
			write(STDOUT_FILENO, &new_str[j], 1);
			j++;
		}
		free(new_str);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}

/**
* _env - print the enviroment variables
* @args: arguments
* Return: 0 on success
*/

int _env(char **args)
{
	int i = 0, j = 0, len = 0;

	while (environ[i])
	{
		len = _strlen(environ[i]);
		while (environ[i][j])
		{
			write(STDOUT_FILENO, &environ[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		j = 0;
		i++;
	}
	return (0);
}
