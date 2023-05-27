#include "shell.h"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **argv);
int shell_ctrld(char **args);

char *builtins[] = {"cd", "help", "exit", "^D", "setenv", "unsetenv"};

int (*builtin_func[]) (char **) = {
	&shell_cd, &shell_help,
	&shell_exit, &shell_ctrld, &_setenv, &_unsetenv};

/**
 * shell_exit - exits the shell
 * @argv: the command-line arguments
 *
 * Return: 0 to signal to exit the shell
 */
int shell_exit(char **argv)
{
	(void)argv;

	return (0);
}

/**
 * shell_cd - changes the current directory
 * @args: the command-line arguments
 *
 * Return: 0 on success, -1 on failure
 */
int shell_cd(char **args)
{
	if (args[1])
	{
		if (chdir(args[1]) != 0)
		{
			perror("cd");
			return (-1);
		}
	}
	else
	{
		chdir(getenv("HOME"));
	}

	return (0);
}
/**
 * shell_ctrld - builtin to handle "^D" call
 * @args: List of args.  Not examined.
 * Return: Always returns 0, to terminate execution.
 */
int shell_ctrld(char **args)
{
	(void)args;
	free(args);
	return (200);
}

/**
 * num_builtins - size
 * Return: size
 */

int num_builtins(void)
{
	return (sizeof(builtins) / sizeof(char *));
}

/**
 * shell_help - prints the help for the shell
 * @args: List of args.  Not examined.
 * Return: Always returns 1, to continue executing.
 */
int shell_help(char **args)
{
	int i;

	printf("For help, call 911\n");
	(void)args;
	for (i = 0; i < num_builtins(); i++)
	{
		printf("  %s\n", builtins[i]);
	}

	return (1);
}

/**
 *_fork - foo that create a fork.
 *@argc: Command and values path.
 *@argv: Has the name of our program.
 *@env: Environment
 *@line: Command line for the user.
 *@pd: ID of proces.
 *@check: Checker add new test
 *Return: 0 success
 */

int _fork(char **argc, char **argv, char **env, char *line, int pd, int check)
{

	pid_t child;
	int status, i = 0;
	char *format = "%s: %d: %s: not found\n";

	if (argc[0] == NULL)
		return (1);
	for (i = 0; i < num_builtins(); i++)
	{
		if (_strcmp(argc[0], builtins[i]) == 0)
			return (builtin_func[i](argc));
	}
	child = fork();
	if (child == 0)
	{
		if (execve(argc[0], argc, env) == -1)
		{
			fprintf(stderr, format, argv[0], pd, argc[0]);
			if (!check)
				free(argc[0]);
			free(argc);
			free(line);
			exit(errno);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (0);
}
