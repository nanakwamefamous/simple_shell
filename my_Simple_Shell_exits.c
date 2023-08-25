#include "my_Simple_Shell_shell.h"
/**
 **myfun__strncpy - is to copies a string
 *@dest: is a destination string to be copied to
 *@src: is a source string
 *@n: the amount of characters to be copied
 *Return: concatenated string
 */
char *myfun__strncpy(char *dest, char *src, int n)
{
	int u, o;
	char *s = dest;

	u = 0;
	while (src[u] != '\0' && u < n - 1)
	{
		dest[u] = src[u];
		u++;
	}
	if (u < n)
	{
		o = u;
		while (o < n)
		{
			dest[o] = '\0';
			o++;
		}
	}
	return (s);
}

/**
 **myfun__strncat - is to concatenates two strings
 *@dest: is a first string
 *@src: is a second string
 *@n: the amount of bytes to be maximally used
 *Return: concatenated string
 */
char *myfun__strncat(char *dest, char *src, int n)
{
	int v, o;
	char *s = dest;

	v = 0;
	o = 0;
	while (dest[n] != '\0')
		v++;
	while (src[o] != '\0' && o < n)
	{
		dest[v] = src[o];
		v++;
		o++;
	}
	if (o < n)
		dest[v] = '\0';
	return (s);
}

/**
 **myfun__strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: always return (s) a pointer to the memory area s
 */
char *myfun__strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
