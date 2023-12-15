#include "shell.h"

/**
* prompt - function prompt
* Return: zero
*/
int prompt(void)
{
	char *prmt = "$ ";
	ssize_t count = 0;

	if (isatty(STDIN_FILENO) == 1)
	{
		count = write(STDOUT_FILENO, prmt, 2);
		if (count == -1)
			exit(0);
	}
	return (0);
}

/**
* *_pathfbuff - function
* @arg: parametre
* @PATH: parametre
* @copy: parametre
* Return: zero
*/
char *_pathfbuff(char **arg, char *PATH, char *copy)
{
	char *token, *concat = NULL, *path = NULL;
	int pathfflag = 0;
	int len = 0, z = 0, count = 0;
	struct stat M;
	static char temp[256];

	copy = NULL;
	copy = _strdup(PATH);
	count = _splitPATH(copy);
	token = _strtok(copy, ": =");
	while (token != NULL)
	{
		concat = _con_cat(temp, arg, token);
		if (stat(concat, &M) == 0)
		{
			path = concat;
			pathfflag = 1;
			break;
		}
		if (z < count - 2)
		{
			len = _strlen(token);
			if (token[len + 1] == ':')
			{
				if (stat(arg[0], &M) == 0)
				{
					path = arg[0];
					pathfflag = 1;
					break;
				}
			}
		}
		z++;
		token = _strtok(NULL, ":");
	}
	if (pathfflag == 0)
		path = arg[0];
	free(copy);
	return (path);
}

/**
* _proc_fork - int function
* @arg: parametre
* @buff: parametre
* @fpb: parametre
* Return: zero
*/

int _proc_fork(char **arg, char *buff, char *fpb)
{
	int a, stat, result, exitstat = 0;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		exit(1);
	}
	if (pid == 0)
	{
		result = execve(fpb, arg, environ);
		if (result == -1)
		{
			perror(arg[0]);
			for (a = 0; arg[a]; a++)
				free(arg[a]);
			free(arg);
			free(buff);
			exit(127);
		}
	}
	wait(&stat);
	if (WIFEXITED(stat))
	{
		exitstat = WEXITSTATUS(stat);
	}
	for (a = 0; arg[a]; a++)
		free(arg[a]);
	free(arg);
	free(buff);
	return (exitstat);
}