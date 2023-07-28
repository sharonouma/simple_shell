#include "shell.h"

int shell_cd(char **args);
int shell_help(char **args);
int shell_exit(char **argv);
int shell_ctrld(char **args);

char *builtins[] = {"cd", "help", "exit", "^D", "setenv", "unsetenv"};

int (*builtin_func[]) (char **) = {
	&shell_cd, &shell_help,
	&shell_exit, &shell_ctrld, &_setenv, &_unsetenv};

int shell_exit(char **argv)
{
	(void)argv;

	return (0);
}

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

int shell_ctrld(char **args)
{
	(void)args;
	free(args);
	return (200);
}

int num_builtins(void)
{
	return (sizeof(builtins) / sizeof(char *));
}

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
