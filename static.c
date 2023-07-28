#include "shell.h"
#define BUFFER_SIZE 1024

char *read_input(void);
int find_newline(char *buffer, int size);
char *copy_line(char *buffer, int len, char *line);
void shift_buffer(char *buffer, int size, int pos);

char *_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static int pos;
	static int size;
	int newline_pos;
	int len;
	char *line = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
	while (1)
	{
		if (pos >= size)
		{
			size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (size <= 0)
			{
				return (NULL);
			}
			pos = 0;
		}

		newline_pos = find_newline(buffer + pos, size - pos);
		if (newline_pos == -1)
		{
			newline_pos = size - pos;
		}
		else
		{
			newline_pos += 1;
		}

		len = newline_pos;
		line = copy_line(buffer + pos, len, line);

		shift_buffer(buffer, size, pos + len);
		size -= pos + len;
		pos = 0;

		return (line);
	}
}
char *read_input(void)
{
	static char buffer[BUFFER_SIZE];
	static int size;

	size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
	if (size <= 0)
	{
		return (NULL);
	}

	return (buffer);
}

int find_newline(char *buffer, int size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		if (buffer[i] == '\n')
		{
			return (i);
		}
	}
	return (-1);
}

char *copy_line(char *buffer, int len, char *line)
{
	char *temp;
	int i;

	temp = realloc(line, len + 1);
	if (temp == NULL)
	{
		free(line);
		return (NULL);
	}
	line = temp;
	for (i = 0; i < len; i++)
	{
		line[i] = buffer[i];
	}
	line[len] = '\0';

	return (line);
}

void shift_buffer(char *buffer, int size, int pos)
{
	int i;

	for (i = 0; i < size - pos; i++)
	{
		buffer[i] = buffer[pos + i];
	}
}
