#include "shell.h"

/**
* main - main function
* Return: 0
*/

int main(void)
{
	char *fpb = NULL, *copy = NULL, *buff = NULL;
	char *PATH = NULL;
	int exitstat = 0;
	char **arg;

	signal(SIGINT, SIG_IGN);
	PATH = get_env("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		arg = NULL;
		prompt();
		buff = _reaad();

		if (*buff != '\0')
		{
			arg = split(buff);
			if (arg == NULL)
			{
				free(buff);
				continue;
			}
			fpb = _pathfbuff(arg, PATH, copy);

			if (checks(arg, buff, exitstat) == 1)
				continue;
			exitstat = _proc_fork(arg, buff, fpb);
		}
		else
			free(buff);
	}

	return (0);
}

/**
* int hsh - main function
* Return: 0
*/
int hsh(info_t*, char**)
{
	char *fpb = NULL, *copy = NULL, *buff = NULL;
	char *PATH = NULL;
	int exitstat = 0;
	char **arg;

	signal(SIGINT, SIG_IGN);
	PATH = get_env("PATH");
	if (PATH == NULL)
		return (-1);
	while (1)
	{
		arg = NULL;
		prompt();
		buff = _reaad();

		if (*buff != '\0')
		{
			arg = split(buff);
			if (arg == NULL)
			{
				free(buff);
				continue;
			}
			fpb = _pathfbuff(arg, PATH, copy);

			if (checks(arg, buff, exitstat) == 1)
				continue;
			exitstat = _proc_fork(arg, buff, fpb);
		}
		else
			free(buff);
	}

	return (0);
}

/**
* char* dup_chars - main function
* Return: 0
*/
char* dup_chars(char*, int, int)
{
	char *dup = NULL;
	int i = 0, j = 0;

	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (dup == NULL)
		return (NULL);
	while (j < i)
	{
		dup[j] = str[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

/**
* char* _pathfbuff - main function
* Return: 0
*/
char* _pathfbuff(char**, char*, char*)
{
	return nullptr;
}

/**
* char* find_path - main function
* Return: 0
*/
char* find_path(info_t*, char*, char*)
{
	return nullptr;
}
