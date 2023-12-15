#include "shell.h"

/**
* _strtok - split the string be delimiter
* @dlm: delimiter
* @str: inpust of string
* Return: string splited
*/

char *_strtok(char str[], const char *dlm)
{
	static char *splited, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		size_t len = _strlen(dlm);

		if (_strncmp(str, dlm, len) == 0)
			return (NULL);
		splited = str; /*stckage 1st adress*/
		i = _strlen(str);
		str_end = &str[i]; /*stockage last adress*/
	}
	str_start = splited;
	if (str_start == str_end)
		return (NULL);
	for (bool = 0; *splited; splited++)
	{
		/*Break the loop and find the next token*/
		if (splited != str_start)
			if (*splited && *(splited - 1) == '\0')
				break;
		/*replace delimiter for NULL char**/
		for (i = 0; dlm[i]; i++)
		{
			if (*splited == dlm[i])
			{
				*splited = '\0';
				if (splited == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splited)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}
