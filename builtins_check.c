#include "shell.h"

/**
 * check_for_builtin - checks if the command is a builtin.
 * @args_array: arguments array
 *
 * Return: 1 if command is a builtin, 0 otherwise
 */
int check_for_builtin(char **args_array)
{
	if (!args_array[0])
		return (0);
	if (_strcmp(args_array[0], "exit"))
		shell_exit(args_array);
	else if (_strcmp(args_array[0], "env"))
		shell_env();
	else if (_strcmp(args_array[0], "setenv"))
		shell_setenv(args_array);
	else if (_strcmp(args_array[0], "unsetenv"))
		shell_unsetenv(args_array);
	else if (_strcmp(args_array[0], "help"))
		shell_help();
	else if (_strcmp(args_array[0], "cd"))
		shell_cd(args_array);
	else if (_strcmp(args_array[0], "clear"))
		shell_clear(args_array);
	else
		return (0);
	return (1);
}
