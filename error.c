#include "shell.h"

/**
 * _puts - is to Prints a string to the standard output stream.
 * @string: The string 
 *
 * Return: Void
 */
void _puts(char *string)
{
	size_t MY_len;
	ssize_t MY_num_written;

	MY_len = _strlen(string);
	MY_num_written = write(STDOUT_FILENO, string, MY_len);
	if (MY_num_written == -1)
	{
		perror("write");
	}
}

/**
 * _puterror - Prints an error message to the standard error stream.
 * @error: message to print when an error occurs.
 *
 * Return: Void
 */
void _puterror(char *error)
{
	size_t MY_len;
	ssize_t MY_num_written;

	MY_len = _strlen(error);
	MY_num_written = write(STDERR_FILENO, error, MY_len);
	if (MY_num_written == -1)
	{
		perror("write");
	}
}
