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
		shellexit(argsarray);
	else if (_strcmp(argsarray[0], "env"))
		shellenv();
	else if (_strcmp(argsarray[0], "setenv"))
		shellsetenv(argsarray);
	else if (_strcmp(argsarray[0], "unsetenv"))
		shellunsetenv(argsarray);
	else if (_strcmp(argsarray[0], "help"))
		shellhelp();
	else if (_strcmp(argsarray[0], "cd"))
		shellcd(argsarray);
	else if (_strcmp(argsarray[0], "clear"))
		shellclear(argsarray);
	else
		return (0);
	return (1);
}
