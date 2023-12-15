#include "shell.h"

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **s; /* s = array of words */

	if (str == NULL || str[0] == 0)
		return (NULL); /* if str is NULL or empty, return NULL */
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++; /* count the number of words in str */
	if (numwords == 0)
		return (NULL); /* if no words, return NULL */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL); /* if malloc fails, return NULL */
	for (i = 0, j = 0; j < numwords; j++) /* for each word */
	{
		while (str[i] == d && str[i] != d)
			i++; /* skip delimiters */
		k = 0; /* reset word length */
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++; /* count word length */
		s[j] = malloc((k + 1) * sizeof(char)); /* allocate memory for word */
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]); /* if malloc fails, free all previous words */
			free(s); /* free array of words */
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++]; /* copy word into array */
		s[j][m] = 0; /* add null byte */
}
	s[j] = NULL; /* add null pointer */
	return (s);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: a pointer to the new string, or NULL on failure
 */

char *_strdup(char *str)
{
	char *s; /* the new string */
	int i, len = 0; /* i = index, len = string length */

	if (str == NULL)
		return (NULL); /* if str is NULL, return NULL */
	while (str[len])
		len++; /* count string length */
	s = malloc((len + 1) * sizeof(char)); /* allocate memory for new string */
	if (!s)
		return (NULL); /* if malloc fails, return NULL */
	for (i = 0; i < len; i++)
		s[i] = str[i]; /* copy string into new string */
	s[i] = 0; /* add null byte */
	return (s); /* return pointer to new string */
}

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	/* i = str index, j = word index, k = word len, m = char index */
	int i, j, k, m, numwords = 0;
	char **s; /* s = array of words */

	if (str == NULL || str[0] == 0)
		return (NULL); /* if str is NULL or empty, return NULL */
	if (!d)
		d = " "; /* if d is NULL, set d to " " */
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++; /* count the number of words in str */

	if (numwords == 0)
		return (NULL); /* if no words, return NULL */
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL); /* if malloc fails, return NULL */
	for (i = 0, j = 0; j < numwords; j++)
	{/* for each word */
		while (is_delim(str[i], d))
			i++; /* skip delimiters */
		k = 0; /* reset word length */
		while (!is_delim(str[i + k], d) && str[i + k])
			k++; /* count word length */
		s[j] = malloc((k + 1) * sizeof(char)); /* allocate memory for word */
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0; /* add null byte */
	}
	s[j] = NULL;
	return (s);
}
