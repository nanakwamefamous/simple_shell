#include "shell.h"

/**
 * main - implements a simple shell
 *
 * Return: EXIT_SUCCESS.
 */
int main(void)
{
	char *MY_input;
	char **args_array;
	int MY_status;

	/* Register signal handlers */
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGTSTP, handle_sigstp);

	do {
		MY_input = get_input();
		if (!MY_input || !*MY_input)/* EOF detected, exit the loop */
			break;

		args_array = tokenize_input(MY_input);
		if (!args_array || !*args_array)
		{
			free(MY_input);
			free_tokens(args_array);
			continue;
		}
		MY_status = execute(args_array);
		free(MY_input);
		free_tokens(args_array);

		/* Set status to 1 to continue the loop */
		MY_status = 1;
	} while (MY_status);

	return (EXIT_SUCCESS);
}
