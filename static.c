#include "shell.h"
#define BUFFER_SIZE 1024

char *read_input(void);
int find_newline(char *buffer, int size);
char *copy_line(char *buffer, int len, char *line);
void shift_buffer(char *buffer, int size, int pos);

/**
 * _getline - Reads a line of input from the user
 *
 * Return: The input line as a char
 */


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

/**
 * read_input - Reads input from the user
 *
 * Return: The input as a character
 */

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

/**
 * find_newline - Finds the position of a newline character in a buffer
 *
 * @buffer: Pointer to the buffer containing the data
 * @size: Size of the buffer
 *
 * Return: The position of the newline character as an integer
 */


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

/**
 * copy_line - Copies a line from a buffer
 *
 * @buffer: Buffer containing the line
 * @len: Length of the line
 * @line: Pointer to store the copied line
 *
 * Return: The copied line as a character
 */


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

/**
 * shift_buffer - Shifts the contents of a buffer
 *
 * @buffer: Pointer to the buffer to be shifted
 * @size: Size of the buffer
 * @pos: Position from where the shift starts
 *
 * Return: void
 */


void shift_buffer(char *buffer, int size, int pos)
{
	int i;

	for (i = 0; i < size - pos; i++)
	{
		buffer[i] = buffer[pos + i];
	}
}
