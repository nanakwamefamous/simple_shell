#include "shell.h"

/**
 * checkforbuiltin - checks if the command is a builtin.
 * @argsarray: arguments array
 *
 * Return: 1 if command is a builtin, 0 otherwise
 */
int checkforbuiltin(char **argsarray)
{
	if (!argsarray[0])
		return (0);
	if (_strcmp(argsarray[0], "exit"))
		shell_exit(argsarray);
	else if (_strcmp(argsarray[0], "env"))
		shell_env();
	else if (_strcmp(args_array[0], "execute"))
		execute();
	else if (_strcmp(argsarray[0], "setenv"))
		shell_setenv(argsarray);
	else if (_strcmp(argsarray[0], "unsetenv"))
		shell_unsetenv(argsarray);
	else if (_strcmp(argsarray[0], "help"))
		shell_help();
	else if (_strcmp(argsarray[0], "cd"))
		shell_cd(argsarray);
	else if (_strcmp(argsarray[0], "clear"))
		shell_clear(argsarray);
	else
		return (0);
	return (1);
}
