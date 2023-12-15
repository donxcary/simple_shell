#include "shell.h"

/**
 * read_char - read a character from the stream and check for errors
 * @t: pointer to the character to store the input
 * @buffer: buffer that stores the input
 * @input: number of bytes read so far
 * Return: number of bytes read, or -1 on error
 */
int read_char(char *t, char *buffer, ssize_t input)
{
	int i;

	i = read(STDIN_FILENO, t, 1);
	if (i == -1 || (i == 0 && input == 0))
	{
		free(buffer);
		return (-1);
	}
	return (i);
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
		i = read_char(&t, buffer, input); /* call the helper function */
		if (i == -1)
			return (-1);
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
				i = read_char(&t, buffer, input); /* call the helper function */
				if (i == -1)
					return (-1);
			}
			if (i == 0)
				break;
			buffer[input] = t;
			input++;
		}
	}
	buffer[input] = '\0';
	bring_line(lineptr, buffer, n, input);
	retval = input;
	if (i !== 0)
		input = 0;
	return (retval);
}