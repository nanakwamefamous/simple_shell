#include "my_Simple_Shell_shell.h"

/**
 * myfun__eputs - is to prints an input string
 *
 * @str: is a string to be printed
 *
 *
 * Return: 0
 */
void myfun__eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		myfun__eputchar(str[n]);
		n++;
	}
}

/**
 * myfun__eputchar - is to writes the character c to stderr
 * @c: is a character to print
 *
 * Return: On success 1, On error, -1 is returned
 * and errno is set appropriately.
 */
int myfun__eputchar(char c)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * myfun__putfd - is to writes the character c to given fd
 *
 * @c: is a character to print
 *
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned
 * and errno is set appropriately.
 */
int myfun__putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 * myfun__putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int myfun__putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += myfun__putfd(*str++, fd);
	}
	return (n);
}
