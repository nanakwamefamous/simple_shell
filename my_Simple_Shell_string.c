#include "my_Simple_Shell_shell.h"
/**
 * myfun__strcat - is to concatenates two strings
 * @dest: destination buffer
 * @src: source buffer
 *
 * Return: to pointer to destination buffer
 */
char *myfun__strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

/**
 * myfun__strcmp -is to performs lexicogarphic comparison of two strangs.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int myfun__strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * myfun_starts_with - is to checks if needle starts with haystack
 * @haystack: is a string to search
 *
 * @needle: is a substring to find
 *
 * Return: to address of next char of haystack or NULL
 */
char *myfun_starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * myfun__strlen - is to returns the length of a string
 *
 * @s: is a string whose length to check
 *
 * Return: integer length of string
 */
int myfun__strlen(char *s)
{
	int n = 0;

	if (!s)
		return (0);

	while (*s++)
		n++;
	return (n);
}
