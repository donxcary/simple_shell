#include "shell.h"

/**
* read_char - read a character from standard input
* Return: the character read, or -1 on error or end of file
*/
int read_char(void)
{
	char t;
	int i;

	i = read(STDIN_FILENO, &t, 1);
	if (i == -1 || i == 0)
		return (-1);
	return (t);
}

/**
* skip_spaces - skip any consecutive spaces in the input
* Return: the next non-space character, or -1 on error or end of file
*/
int skip_spaces(void)
{
	int t;

	t = read_char();
	while (t == ' ')
		t = read_char();
	return (t);
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
	char* buffer, t = 'z';

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
		t = read_char();
		if (t == -1)
		{
			free(buffer);
			return (-1);
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
			t = skip_spaces();
			if (t == -1)
				break;
			buffer[input] = t;
			input++;
		}
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (t != -1)
		input = 0;
	return (retval);
}