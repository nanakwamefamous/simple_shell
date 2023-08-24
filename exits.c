#include "shell.h"

/**
 **_strncpy - is to copies a string
 *@dest: is a destination string to be copied to
 *@src: is a source string
 *@n: the amount of characters to be copied
 *Return: concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int n, o;
	char *s = dest;

	n = 0;
	while (src[n] != '\0' && n < n - 1)
	{
		dest[n] = src[n];
		n++;
	}
	if (n < n)
	{
		o = n;
		while (o < n)
		{
			dest[o] = '\0';
			o++;
		}
	}
	return (s);
}

/**
 **_strncat - is to concatenates two strings
 *@dest: is a first string
 *@src: is a second string
 *@n: the amount of bytes to be maximally used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int n, o;
	char *s = dest;

	n = 0;
	o = 0;
	while (dest[n] != '\0')
		n++;
	while (src[o] != '\0' && o < n)
	{
		dest[n] = src[o];
		n++;
		o++;
	}
	if (o < n)
		dest[n] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: always return (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
