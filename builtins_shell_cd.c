#include "shell.h"

/**
 * shell_cd - is to changes the current directory of the shell.
 * @args_array: array arguments.
 */
void shell_cd(char **args_array)
{
	char *MY_dir = args_array[1];
	int MY_ret;

	/* If no argument array is provided, change to HOME directory */
	if (MY_dir == NULL)
	{
		MY_dir = _getenv("HOME");
		if (MY_dir == NULL)
		{
			_puts("cd: No HOME directory found\n");
			return;
		}
	}

	MY_ret = chdir(MY_dir);
	if (MY_ret == -1)
	{
		perror("cd");
	}
}
