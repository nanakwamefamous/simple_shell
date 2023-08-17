#include "shell.h"

/**
 * shell_exit - Exit the shell.
 * @args_array: Arguments array.
 *
 * Return: 0 .
 */
void shell_exit(char **args_array)
{
	int MY_status = 0;

	if (args_array[1] != NULL)
	{
		MY_status = _atoi(args_array[1]);
	}
	free_tokens(args_array);
	free_last_input();
	exit(MY_status);
}
