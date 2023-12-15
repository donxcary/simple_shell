#include "shell.h"

/**
* _splitstring - function
*@s:argument
*Return: int
*/
int _splitstring(char *s)
{
	int i;
	int srcflg = 1;
	int cmp = 0;

	for (i = 0; s[i]; i++)
	{
		if (s[i] != ' ' && srcflg == 1)
		{
			cmp += 1;
			srcflg = 0;
		}
		if (s[i + 1] == ' ')
			srcflg = 1;
	}
	return (cmp);
}


/**
* split - split inputs to tokens
* @buff: string
*
* Return: tokens
*/
char **split(char *buff)
{
	const char *delimiters = " \n";
	const char *tokens;
	int number_tokens = 0, i = 0;
	char **arg;

	number_tokens = _splitstring(buff);
	if (!number_tokens)
		return (NULL);
	arg = malloc((number_tokens + 1) * sizeof(char *));
	if (arg == NULL)
		exit(1);

	/* Split the input string to an array */
	tokens = _strtok(buff, delimiters);

	while (tokens != NULL)
	{
		arg[i] = _strdup(tokens);
		tokens = _strtok(NULL, delimiters);
		i++;
	}
	arg[i] = NULL;
	return (arg);
}
