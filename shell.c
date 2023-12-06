#include "shell.h"

/**
 * main - main function
 * @argc: number of arguments
 * @argv: arguments
 * @env: environment
 * Return: 0
 */

int main(int argc, char **argv, char **env)
{
	char *line = NULL, **tokens = NULL, *path = NULL;
	size_t len = 0;
	int status = 0, i = 0, j = 0, k = 0, count = 0;
	pid_t child_pid;

	(void)argc;
	signal(SIGINT, sigint_handler);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(status);
		}
		if (line[0] == '\n')
			continue;
		tokens = tokenizer(line);
		if (tokens == NULL)
			continue;
		if (tokens[0] == NULL)
		{
			free(tokens);
			continue;
		}
		if (tokens[0][0] == '/')
			path = tokens[0];
		else
			path = get_path(tokens[0], env);
		if (path == NULL)
		{
			free(tokens);
			continue;
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			free(tokens);
			free(path);
			exit(1);
		}
		if (child_pid == 0)
		{
			if (execve(path, tokens, NULL) == -1)
			{
				perror("Error");
				free(tokens);
				free(path);
				exit(1);
			}
		}
		else
		{
			wait(&status);
			free(path);
			free(tokens);
		}
	}
	free(line);
	return (status);
}

/**
 * tokenizer - tokenizes a string
 * @line: string to tokenize
 * Return: array of tokens
 */

char **tokenizer(char *line)
{
	char **tokens = NULL, *token = NULL;
	int i = 0, j = 0, count = 0;

	count = count_tokens(line);
	if (count == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
	{
		perror("Error");
		return (NULL);
	}
	token = strtok(line, " \n\t\r");
	while (token != NULL)
	{
		tokens[i] = malloc(sizeof(char) * (_strlen(token) + 1));
		if (tokens[i] == NULL)
		{
			perror("Error");
			free(tokens);
			return (NULL);
		}
		for (j = 0; token[j] != '\0'; j++)
			tokens[i][j] = token[j];
		tokens[i][j] = '\0';
		token = strtok(NULL, " \n\t\r");
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
 * count_tokens - counts the number of tokens in a string
 * @line: string to count tokens in
 * Return: number of tokens
 */

int count_tokens(char *line)
{
	int i = 0, count = 0;

	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '\n' || line[i] == '\t' ||
		    line[i] == '\r')
		{
			i++;
			continue;
		}
		while (line[i] != ' ' && line[i] != '\n' && line[i] != '\t' &&
		       line[i] != '\r' && line[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

/**
 * get_path - gets the path of a command
 * @command: command to get path of
 * @env: environment
 * Return: path of command
 */

char *get_path(char *command, char **env)
{
	char *path = NULL, *token = NULL, *path2 = NULL;
	int i = 0, j = 0, k = 0, l = 0;

	while (env[i] != NULL)
	{
		if (_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = malloc(sizeof(char) * (_strlen(env[i]) + 1));
			if (path == NULL)
			{
				perror("Error");
				return (NULL);
			}
			for (j = 5; env[i][j] != '\0'; j++)
				path[j - 5] = env[i][j];
			path[j - 5] = '\0';
			break;
		}
		i++;
	}
	token = strtok(path, ":");
	while (token != NULL)
	{
		path2 = malloc(sizeof(char) * (_strlen(token) + _strlen(command) + 2));
		if (path2 == NULL)
		{
			perror("Error");
			free(path);
			return (NULL);
		}
		for (k = 0; token[k] != '\0'; k++)
			path2[k] = token[k];
		path2[k] = '/';
		k++;
		for (l = 0; command[l] != '\0'; l++)
			path2[k + l] = command[l];
		path2[k + l] = '\0';
		if (access(path2, F_OK) == 0)
		{
			free(path);
			return (path2);
		}
		free(path2);
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}