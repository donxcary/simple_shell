#include "shell.h"

/**
* bring_line - assigns the line  var for the get_line
* @lineptr: the buffer that store the input string
* @buffer: the string that has been called to the line
* @n: the size of the line
* @j: the size of the buffer
*/
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j)
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

/**
* get_line - read the input from stream
* @lineptr: buffer that stores the input
* @n: the size of lineptr
* @stream: the stream to read from
* Return: num of bytes
*/
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer, t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;
	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == NULL)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
		{
			buffer = _realloc(buffer, input, input + 1);
			if (buffer == NULL)
				return (-1);
		}
		buffer[input] = t;
		input++;
		if (t == ' ')
		{
			while (i == 1 && t == ' ')
			{
				i = read(STDIN_FILENO, &t, 1);
				if (i == -1)
				{
					free(buffer);
					return (-1);
				}
			}
			if (i == 0)
				break;
			buffer[input] = t;
			input++;
		}
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}
