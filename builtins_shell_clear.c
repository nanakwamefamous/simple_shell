#include "shell.h"

/**
 * shell_clear - is to clears the terminal.
 * @args_array: array of arguments.
 *
 * Return: 1 to continue executing,
 *         or 0 to exit.
*/
int shell_clear(char **args_array)
{
	(void)args_array; /* avoid "unsued parameter" warning */
	_puts("\033[2J\033[H");
	return (1);
}