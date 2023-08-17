#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @string: the string whose length to check
 *
 * Return: string
 */
int _strlen(const char *string)
{
	int n = 0;

	if (!string)
		return (0);

	while (*string++)
		n++;
	return (n);
}

/**
 * _strcmp - Compare two strings.
 * @str1: The first string to compare.
 * @str2: The second string to compare.
 * Return: 0 if @str1 and @str2 are equal,
 *         a negative value if @str1 is less than @str2,
 *         or a positive value if @str1 is greater than @str2.
 */
int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return ((int) (*str1) - (*str2));
}

/**
 * _strncmp - Compare two strings up to a specified length.
 * @str1: First string to compare.
 * @str2: Second string to compare.
 * @n: Maximum number of characters to compare.
 *
 * Return: 0 if the strings are equal up to n characters, negative value
 *         if str1 is less than str2, or positive value if str1
 * is greater than str2.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char u1, u2;

	while (n-- > 0)
	{
		u1 = (unsigned char) *str1++;
		u2 = (unsigned char) *str2++;

		if (u1 != u2)
			return (u1 - u2);
		if (u1 == '\0')
			break;
	}

	return (0);
}

/**
 * _strstr - checks if my_needle starts with my_haystack
 * @my_haystack: string to search
 * @my_needle: the substring to find
 *
 * Return: address of next char of my_haystack or NULL
 */
char *_strstr(char *my_haystack, char *my_needle)
{
	int n;

	for (n = 0; my_haystack[n] != '\0'; n++)
	{
		if (my_haystack[n] == my_needle[0])
		{
			int e;

			for (e = 0; my_needle[e] != '\0'; e++)
			{
				if (my_haystack[n + e] != my_needle[e])
				{
					break;
				}
			}

			if (my_needle[e] == '\0')
			{
				return (&my_haystack[n]);
			}
		}
	}
	return (NULL);
}

/**
 * _strchr - a function that locates a character in a string
 *
 * @string:  string array input
 * @character: character to locate from input array
 *
 * Return: first occurence of charatcer or null if not found
*/

char *_strchr(char *string, char character)
{
	while (*string != '\0')
	{
		if (*string == character)
			return (string);
		string++;}
	if (*string == character)
		return (string);
	return (NULL);
}
