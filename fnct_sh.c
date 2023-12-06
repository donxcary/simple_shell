#include "shell.h"


/**
 * prompt - prompt
 * Return: int
 */

int prompt(void)
{
	char *line = NULL;
	char **args = NULL;
	int status = 0;

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		line = _read();
		if (line == NULL)
			return (0);
		args = _parse(line);
		if (args == NULL)
			return (0);
		status = _execute(args);
		free(line);
		free(args);
	}
	return (status);
}

/**
 * _path - find the path
 * @args: arguments	
 * @PATH: arguments
 * @copy: arguments	
 * Return: ptr
 */

char *_path(char **args, char *PATH, char *copy)
{
	char *ptr = NULL;
	char *token = NULL;
	int i = 0;

	token = strtok(PATH, ":");
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
		token = strtok(NULL, ":");
		i = 0;
	}
	free(copy);
	return (NULL);
}

/**
 * _proc_fork - execute a command
 * @args: arguments
 * @buff: parameters
 * @fpb: parameters
 * @PATH: parameters
 * Return: 0 on success
 */

int _proc_fork(char **args, char *buff, char *fpb, char *PATH)
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
		free(buff);
		free(fpb);
		free(PATH);
	}
	return (status);
}