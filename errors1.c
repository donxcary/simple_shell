#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
int _erratoi(char *s)
{
	int i = 0; /* index */
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10; /* shift left 1 decimal place */
			result += (s[i] - '0'); /* add the next digit */
			if (result > INT_MAX)
				return (-1); /* overflow */
		}
		else
			return (-1); /* not a number */
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname); /* TODO: why does this make main return 255? */
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of char printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0; /* index */
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0) /* if negative, print '-' and negate */
	{
		_abs_ = -input;
		__putchar('-'); /* print '-' */
		count++; /* increment count */
	}
	else
		_abs_ = input; /* else, just print the number */
	current = _abs_; /* set current to _abs_ */
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i) /* if current digit is not 0 */
		{
			__putchar('0' + current / i); /* print current digit */
			count++;
		}
		current %= i; /* remove current digit */
	}
	__putchar('0' + current); /* print last digit */
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: pointer to converted string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50]; /* 50 is big enough for any base 2-16 */
	char sign = 0; /* sign is only used for base 10 */
	char *ptr; /* ptr points to the last character in buffer */
	unsigned long n = num; /* unsigned prevents surprises with negative numbers */

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num; /* make n positive */
		sign = '-'; /* save the sign */

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49]; /* ptr points to last char in buffer */
	*ptr = '\0'; /* null terminate string */

	do	{
		*--ptr = array[n % base];
		n /= base; /* divide n by base */
	} while (n != 0); /* repeat until n is 0 */

	if (sign)
		*--ptr = sign; /* add sign */
	return (ptr); /* return pointer to first digit */
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0'; /* replace '#' with '\0' */
			break;
		}
}
