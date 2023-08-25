#include "my_Simple_Shell_shell.h"

/**
 * my_interactive - it returns true if shell is my_interactive mode
 * @info: --- struct address
 *
 *
 *
 * Return: 1 if my_interactive mode, or 0
 */
int myfun_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * my_is_delim - is to checks if character is a delimeter
 *
 * @c: is char to check
 *
 * @delim: is delimeter string
 *
 * Return: 1 if true, or 0
 */
int myfun_is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - is to checks for alphabetic character
 *
 * @c: is character to input
 *
 * Return: 1 if c is alphabetic, or 0
 */

int myfun__isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 *
 * @s: the string to be converted
 *
 * @n: the number to be converted
 *
 * Return: 0 if no numbers in string, converted number otherwise
 */

int myfun__atoi(char *s)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; s[n] != '\0' && flag != 2; n++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[n] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[n] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
