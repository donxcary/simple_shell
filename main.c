#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT }; /* info struct */
	int fd = 2; /* stderr */

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY); /* open file */
		if (fd == -1) /* error handling */
		{
			if (errno == EACCES) /* permission denied */
				exit(126); /* exit with 126 */
			if (errno == ENOENT) /* file not found */
			{
				_eputs(av[0]); /* print program name */
				_eputs(": 0: Can't open "); /* print error message */
				_eputs(av[1]); /* print file name */
				_eputchar('\n'); /* print newline */
				_eputchar(BUF_FLUSH); /* flush buffer */
				exit(127); /* exit with 127 */
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; /* set readfd to file descriptor */
	}
	populate_env_list(info); /* populate env list */
	read_history(info); /* read history file */
	hsh(info, av); /* start shell */
	return (EXIT_SUCCESS); /* exit with success */
}
