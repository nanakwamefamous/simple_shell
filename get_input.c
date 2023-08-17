#include "shell.h"

static char *MY_last_input;
/**
 * get_input - Read the line of input from user.
 *
 * Return: Pointer to a buffer conatining the user's input.
*/
char *get_input(void)
{
	char *MY_input = NULL;
	size_t MY_input_size = 0;
	ssize_t n_read;

	do {
		/* print shell prompt */
		prompt();

		/* get a line of input from user */
		n_read = getline(&MY_input, &MY_input_size, stdin);

		/* check for error */
		if (n_read == -1)
		{
			free(MY_input);
			_puts("\n");
			return (NULL);
		}

		/* remove trailing newline character */
		MY_input[n_read - 1] = '\0';

	} while (MY_input[0] == '\0' || isspace(MY_input[0]));

	/* update last_input to point to the new input */
	MY_last_input = MY_input;
	return (MY_input);
}

/**
 * free_last_input - Frees the most recent input entered by the user.
 */
void free_last_input(void)
{
	free(MY_last_input);
	MY_last_input = NULL;
}
