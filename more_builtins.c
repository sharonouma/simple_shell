#include "shell.h"
/**
 * _setenv - Sets the value of an environment variable
 * @args: An array of strings containing the command arguments
 *
 * Return: Always returns 1 to continue executing
 */
int _setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (setenv(args[1], args[2], 1) == -1)
		perror("setenv");

	return (1);
}

/**
 * _unsetenv - Unsets an environment variable
 * @args: An array of strings containing the command arguments
 *
 * Return: Always returns 1 to continue executing
 */
int _unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unsetenv(args[1]) == -1)
		perror("unsetenv");

	return (1);
}
