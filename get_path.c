#include "shell.h"

/**
 * get_path - Returns the value of the PATH.
 *
 * Return: $PATH.
 */
char *get_path(void)
{
	return (_getenv("PATH"));
}
