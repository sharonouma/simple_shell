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
 * shell_exit - Terminates the shell program
 *
 * @argv: The command-line arguments
 *
 * Return: 0 to indicate successful termination of the shell program
 */

int shell_exit(char **argv)
{
	(void)argv;

	return (0);
}

/**
 * shell_cd - Modify the current working directory
 *
 * @args: The command-line arguments specifying the directory path
 *
 * Return: 0 upon successful modification, -1 upon failure
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
 * shell_ctrld - Handle the "^D" command to conclude the shell program
 *
 * @args: Array of arguments (not inspected)
 *
 * Return: Always returns 0 to conclude the execution.
 */

int shell_ctrld(char **args)
{
	(void)args;
	free(args);
	return (200);
}

/**
 * num_builtins - Retrieve the count of built-in commands
 *
 * Return: The count or size of the built-in command collection
 */


int num_builtins(void)
{
	return (sizeof(builtins) / sizeof(char *));
}

/**
 * shell_help - Display the help information for the shell
 *
 * @args: List of arguments (not examined)
 *
 * Return: Always returns 1 to continue executing the shell.
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
 * _fork - Create a child process using fork()
 *
 * @argc: Number of command-line arguments
 * @argv: Array of strings containing the program name and arguments
 * @env: Array of strings representing the environment
 * @line: String containing the command line entered by the user
 * @pd: Process ID of the parent process
 * @check: Additional checker for new tests
 *
 * Return: 0 on success, indicating the child process creation
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
