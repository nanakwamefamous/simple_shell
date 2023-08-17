#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: destination
 */
char *_strcpy(char *destination, char *source)
{
	int n = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[n])
	{
		destination[n] = source[n];
		n++;
	}
	destination[n] = 0;
	return (destination);
}

/**
 * _strcat - concatenates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, const char *source)
{
	char *MY_ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (MY_ret);
}

/**
 * _strdup - duplicate string
 * @string: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int length = 0;
	char *MY_ret;

	if (string == NULL)
		return (NULL);
	while (*string++)
		length++;
	MY_ret = malloc(sizeof(char) * (length + 1));
	if (!MY_ret)
		return (NULL);
	for (length++; length--;)
		MY_ret[length] = *--string;
	return (MY_ret);
}

/**
 *_putchar - writes the character character to stdout
 * @character: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char character)
{
	return (write(1, &character, 1));
}

/**
 * _strspn - a function that gets the
 *           length of a prefix substring
 *
 * @str: pointer to string input
 * @acpt: substring prefix to look for
 *
 * Return: the number of bytes in the initial segment
 */
unsigned int _strspn(char *str, char *acpt)
{
	unsigned int n, e;

	for (n = 0; str[n]; n++)
	{
		for (e = 0; acpt[e]; e++)
		{
			if (str[n] == acpt[e])
				break;
		}
		if (!acpt[e])
			return (n);
	}

	return (n);
}
