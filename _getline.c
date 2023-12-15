#include "shell.h"

/**
 * bring_line - bring a line
 * @lineptr: lineptr
 * @buffer: the string that has been called to getline
 * @n: the size of the line
 * @j: the size of the line
 * Return: line
 */

void bring_line(char **lineptr, char *buffer, size_t n, int j)
{
	int i = 0;

	while (i < j)
	{
		(*lineptr)[i] = buffer[i];
		i++;
	}
	(*lineptr)[i] = '\0';
	free(buffer);
	n = 0;
}

/**
 * _getline - read a line from stdin
 * Return: line
 */

static char *_getline(void)	/* read a line from stdin */
{
	char *line = NULL;
	char *buffer = NULL;
	size_t n = 0;
	int i = 0, j = 0, k = 0;

	buffer = malloc(sizeof(char) * 1024);
	if (buffer == NULL)
		return (NULL);
	while (1)
	{
		i = read(STDIN_FILENO, &buffer[j], 1);
		if (i == -1)
			return (NULL);
		if (buffer[j] == '\n')
		{
			line = malloc(sizeof(char) * (j + 1));
			if (line == NULL)
				return (NULL);
			bring_line(&line, buffer, n, j);
			return (line);
		}
		if (buffer[j] == EOF)
		{
			free(buffer);
			return (NULL);
		}
		j++;
		if (j == 1024)
		{
			line = malloc(sizeof(char) * (j + 1));
			if (line == NULL)
				return (NULL);
			bring_line(&line, buffer, n, j);
			return (line);
		}
	}
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
	
	return (args)

}

/**
* bring_line - assigns the line  var for the get_line
* @lineptr: the buffer that store the input string
* @buffer: the string that has been called to the line
* @n: the size of the line
* @j: the size of the buffer
*/
void bring_line(char** lineptr, size_t* n, char* buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}

}