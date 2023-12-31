#include "my_Simple_Shell_shell.h"
/**
 * myfun__putchar - is to writes the character c to stdout
 *
 * @c: is the character to print
 *
 * Return: On success 1
 * On error, -1 is returned
 */
int myfun__putchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}


/**
 * myfun__strdup - is to duplicates a string
 * @str: is a string to duplicate
 *
 * Return: to pointer to the duplicated string
 */
char *myfun__strdup(const char *str)
{
	int L = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		L++;
	ret = malloc(sizeof(char) * (L + 1));
	if (!ret)
		return (NULL);
	for (L++; L--;)
		ret[L] = *--str;
	return (ret);
}

/**
 * myfun__puts - is to prints an input string
 * @str: is a string to be printed
 *
 * Return: 0
 */
void myfun__puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		myfun__putchar(str[n]);
		n++;
	}
}

/**
 * myfun__strcpy - is to copies a string
 * @dest: is a destination
 * @src: is a source
 *
 * Return: to pointer to destination
 */
char *myfun__strcpy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}
