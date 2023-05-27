#include "shell.h"
/**
 * read_line -  reads input
 * Return: The input.
 */

char *read_line(void)
{
	char *line = NULL;
	size_t buffsize = 0;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	if (getline(&line, &buffsize, stdin) == -1)
	{
		free(line);
		return (NULL);
	}

	return (line);
}
