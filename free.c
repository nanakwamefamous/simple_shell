#include "shell.h"

/**
 * free_error - is to free alloc'd pointers following system error
 * @argv_pointer: pointer to an array of pointers
 * @arg_character: pointer to an array of characters
 *
 * Return: void.
 */
void free_error(char **argv_pointer, char *arg_character)
{
	int n;

	for (n = 0; argv_pointer[n]; n++)
		free(argv_pointer[n]);
	free(argv_pointer);
	free(arg_character);
	exit(EXIT_FAILURE);
}

/**
 * free_tokens - is to free memory allocated dynamically by tokenize().
 * @pointer: pointer to allocated memory.
 *
 * Return: void.
 */
void free_tokens(char **pointer)
{
	int n;

	for (n = 0; pointer[n]; n++)
		free((pointer[n]));
	free(pointer);
}


/**
 * free_path - is to Free the global variable containing the PATH environment
 *              variable value.
 *
 * Return: Nothing
 */
void free_path(void)
{
	if (my_environ != NULL)
	{
		size_t n = 0;

		while (environ[n] != NULL)
		{
			if (_strncmp(my_environ[n], "PATH=", 5) == 0)
			{
				free(my_environ[n]);
				my_environ[n] = NULL;
				break;
			}
			n++;
		}
	}
}
