#include "my_Simple_Shell_shell.h"
/**
 * myfun__erratoi - is to converts a string to an integer
 *
 * @s: is a string to be converted
 *
 * Return: always 0 if no numbers in string,
 *  or converted number -1 on error
 */
int myfun__erratoi(char *s)
{
	int n = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (n = 0;  s[n] != '\0'; n++)
	{
		if (s[n] >= '0' && s[n] <= '9')
		{
			result *= 10;
			result += (s[n] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * myfun_print_error - is to prints an error messages
 *
 * @info: is a parameter & return info struct
 *
 * @estr: is a string containing specified error type
 *
 * Return: 0 if no numbers in string,
 * or converted number -1 on error
 */
void myfun_print_error(info_t *info, char *estr)
{
	myfun__eputs(info->fname);
	myfun__eputs(": ");
	myfun_print_d(info->line_count, STDERR_FILENO);
	myfun__eputs(": ");
	myfun__eputs(info->argv[0]);
	myfun__eputs(": ");
	myfun__eputs(estr);
}

/**
 * myfun_print_d - is to function prints a decimal (integer) number (base 10)
 *
 * @input: is a input
 *
 * @fd: is a filedescriptor to write to
 *
 * Return: to return number of characters printed
 */
int myfun_print_d(int input, int fd)
{
	int (*__putchar)(char) = myfun__putchar;
	int n, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = myfun__eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (n = 1000000000; n > 1; n /= 10)
	{
		if (_abs_ / n)
		{
			__putchar('0' + current / n);
			count++;
		}
		current %= n;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * myfun_convert_number - is to converter function, a clone of itoa
 *
 * @base: base
 *
 * @flags: argument flags
 * @num: number
 * Return: string
 */
char *myfun_convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * myfun_remove_comments - is to function replaces first instance of '#' with '\0'
 * @buf: is a address of the string to modify
 *
 * Return: 0;
 */
void myfun_remove_comments(char *buf)
{
	int n;

	for (n = 0; buf[n] != '\0'; n++)
		if (buf[n] == '#' && (!n || buf[n - 1] == ' '))
		{
			buf[n] = '\0';
			break;
		}
}
