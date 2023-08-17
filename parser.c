#include "shell.h"

/**
 * tokenize - an array string into MY_tokens using a delimiter.
 * @string: the string to be tokenized.
 * @delimiter: the delimiter used to split the string.
 *
 * Return: an array of pointers to the MY_tokens,
 *         or NULL if an error occurs.
 */
char **tokenize(char *string, const char *delimiter)
{
	char *MY_token = NULL;
	char **MY_ret = NULL;
	int n = 0;

	MY_token = strtok(string, delimiter);
	while (MY_token)
	{
		MY_ret = realloc(MY_ret, sizeof(char *) * (n + 1));
		if (MY_ret == NULL)
			return (NULL);

		MY_ret[n] = malloc(_strlen(MY_token) + 1);
		if (!(MY_ret[n]))
			return (NULL);

		_strcpy(MY_ret[n], MY_token);
		MY_token = strtok(NULL, delimiter);
		n++;
	}
	MY_ret = realloc(MY_ret, (n + 1) * sizeof(char *));
	if (!MY_ret)
		return (NULL);

	MY_ret[n] = NULL;
	return (MY_ret);
}

/**
 * tokenize_input - splits a user input string into tokens with tokenize().
 *
 * @my_input: the user input string to be tokenized.
 *
 * Return: an array of pointers to the tokens, or NULL if an error occurs
 */
char **tokenize_input(char *my_input)
{
	char **MY_tokens = NULL;
	char *temp = NULL;

	temp = _strdup(my_input);
	if (temp == NULL)
	{
		_puts("Memory allocation errors\n");
		exit(EXIT_FAILURE);
	}

	MY_tokens = tokenize(temp, " \t\r\n\a");
	free(temp);

	return (MY_tokens);
}
