#include "shell.h"
/**
 * get_path - get variable PATH.
 * @env: enviromente local
 * Return: value of PATH.
 */

char *get_path(char **env)
{
	size_t i = 0, var = 0, count = 5;
	char *path = NULL;

	for (i = 0; _strncmp(env[i], "PATH=", 5); i++)
		;
	if (env[i] == NULL)
		return (NULL);

	for (count = 5; env[i][var]; var++, count++)
		;
	path = malloc(sizeof(char) * (count + 1));

	if (path == NULL)
		return (NULL);

	for (var = 5, count = 0; env[i][var]; var++, count++)
		path[count] = env[i][var];

	path[count] = '\0';
	return (path);
}
