#include "shell.h"
/**
 * tokenize - tokenizes a stirng
 * @lptr: what the user inputed
 * Return: a ptr to arr of ptrs
 */

char **tokenize(char *lptr)
{
	char **tokens = NULL;
	char *token = NULL;
	size_t i = 0;
	int s = 0;

	if (lptr == NULL)
		return (NULL);

	for (i = 0; lptr[i]; i++)
	{
		if (lptr[i] == ' ')
			s++;
	}
	if ((s + 1) == _strlen(lptr))
		return (NULL);
	tokens = malloc(sizeof(char *) * (s + 2));
	if (tokens == NULL)
		return (NULL);

	token = strtok(lptr, " \n\t\r");

	for (i = 0; token != NULL; i++)
	{
		tokens[i] = token;
		token = strtok(NULL, " \n\t\r");
	}
	tokens[i] = NULL;
	return (tokens);
}
