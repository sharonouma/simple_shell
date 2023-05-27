#include "shell.h"


/**
 * _getenv - prints environment to stdout
 *
 * @env: enviroment
 * Return: void
 *
 */

void _getenv(char **env)
{
	size_t i = 0;

	while (env[i])
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
