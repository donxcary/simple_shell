#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to check
 * Return: the length of the string
 */

int _strlen(char *s)
{
	/* count the number of characters in the string */
	int i = 0; /* counter */
	while (s[i])
		i++; /* add 1 to counter for each character */

	return (i);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else /* not alpha */
		return (0);
}

/**
 * is_delim - checks if character is a delimeter character
 * 
 * Description: checks if character is a delimeter character
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim) /* while not at end of string */
		if (*delim++ == c) /* if delim matches c */
			return (1);
	return (0);
}


/**
* interactive - checks if shell is interactive
* @info: the info struct
* Return: 1 if interactive, 0 if not
*/
int interactive(info_t* info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
