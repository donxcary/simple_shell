#include "shell.h"

/**
 * _read - read a line from stdin	
 * Return: line
 */

char *_read(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read = 0;

	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * _parse - parse a line
 * @line: line to parse
 * Return: array of strings
 */

char **_parse(char *line)
{
	char **args = NULL;
	char *token = NULL;
	int i = 0;

	args = malloc(sizeof(char *) * 1024);
	if (args == NULL)
		return (NULL);
	token = strtok(line, " \n");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " \n");
		i++;
	}
	args[i] = NULL;
	return (args);
}


/**
 * _execute - execute a command
 * @args: arguments
 * Return: 0 on success
 */

int _execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("Error");
			return (1);
		}
	}
	else if (pid < 0)
	{
		perror("Error");
		return (1);
	}
	else
	{
		wait(&status);
	}
	return (0);
}