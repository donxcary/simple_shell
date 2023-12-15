#include "shell.h"

/**
* _strncmp - fonction cmopares at most n characters of
*            the strings s1 and s2
*@s1: 1st string
*@s2: 2sec string
*@n: name of each environment
* Return: zero
*/

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		else if (s1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}

/**
* exe_cmd - function that execute the command
* @argv: array of arguments
* Return: zero
*/

int exe_cmd(char** argv)
{
pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else if (pid < 0)
	{
		perror("Error");
	}
	else
	{
		wait(&status);
	}
	return (0);
}

/**
* get_path - function that get the path
* @cmd: command
* Return: zero
*/

char* get_path(char* cmd)
{
	char *path, *token, *path2;
	struct stat st;

	path = _getenv("PATH");
	path2 = malloc(sizeof(char) * 1024);
	token = strtok(path, ":");
	while (token != NULL)
	{
		_strcpy(path2, token);
		_strcat(path2, "/");
		_strcat(path2, cmd);
		if (stat(path2, &st) == 0)
		{
			return (path2);
		}
		token = strtok(NULL, ":");
	}
	return (NULL);
}
