#include "shell.h"
/**
 * value_path - Separate the path in new strings.
 * @argv: Command input of user.
 * @env: Enviroment.
 * Return: Pointer to strings.
 */
int value_path(char **argv, char **env)
{
	char *token = NULL, *rel_path = NULL, *abs_path = NULL;
	size_t val_path, len;
	struct stat stat_lineptr;

	if (stat(*argv, &stat_lineptr) == 0)
		return (-1);
	rel_path = get_path(env);
	if (!rel_path)
		return (-1);
	token = strtok(rel_path, ":");
	len = _strlen(*argv);
	while (token)
	{
		val_path = _strlen(token);
		abs_path = malloc(sizeof(char) * (val_path + len + 2));
		if (!abs_path)
		{
			free(rel_path);
			return (-1);
		}
		abs_path = strcpy(abs_path, token);
		_strcat(abs_path, "/");
		_strcat(abs_path, *argv);

		if (stat(abs_path, &stat_lineptr) == 0)
		{
			*argv = abs_path;
			free(rel_path);
			return (0);
		}
		free(abs_path);
		token = strtok(NULL, ":");
	}
	token = '\0';
	free(rel_path);
	return (-1);
}
