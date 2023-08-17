#include "shell.h"

/**
 * shell_env - is to Prints all the environment variables in shell.
 *
 * Return: void.
 */
int shell_env(void)
{
	int n;

	for ( n = 0; environ[n]; n++)
	{
		_puts(environ[n]);
		_putchar('\n');
	}

	return (0);
}
