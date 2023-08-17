#include "shell.h"

/**
 * shell_setenv -is to Set the array_value of an environment variable
 * @args_array: Arguments array of environment variables
 *
 * Return: 0
 */
int shell_setenv(char **args_array)
{
	char *array_name, *array_value;

	if (args_array[1] == NULL || args_array[2] == NULL)
	{
		_puterror("USAGE: setenv VARIABLE array_VALUE\n");
		return (-1);
	}

	array_name = args_array[1];
	array_value = args_array[2];

	if (setenv(array_name, array_value, 1) != 0)
	{
		_puterror("setenv");
		return (-1);
	}
	return (0);
}

/**
 * shell_unsetenv - Unset an environment variable in the shell.
 * @args_array: Arguments array
 * Return: 0
 */
int shell_unsetenv(char **args_array)
{
	char *array_name;

	if (args_array[1] == NULL)
	{
		_puterror("USAGE: unsetenv VARIABLE\n");
		return (-1);
	}

	array_name = args_array[1];

	if (unsetenv(array_name) != 0)
	{
		_puterror("unsetenv");
	}
	return (0);
}
