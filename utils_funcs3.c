#include "shell.h"

/**
 * _atoi - Converts a string to an integer.
 * @string:  string
 *
 * Return: string.
 */
int _atoi(const char *string)
{
	int n, my_sign;
	unsigned int my_num;

	n = 0;
	my_sign = 1;
	my_num = 0;

	while (string[n] != '\0')
	{
		if (string[n] == '-')
			my_sign *= -1;
		else if (string[n] >= '0' && string[n] <= '9')
			my_num = (my_num * 10) + (string[n] - '0');
		else
			break;
		n++;
	}
	return (my_num * my_sign);
}

/**
 **_memset - fills memory with a constant byte.
 *@str: the pointer to the memory area.
 *@byte: the byte to fill *str with.
 *@n: the amount of bytes to be filled.
 *Return: (str) a pointer to the memory area str
 */
char *_memset(char *str, char byte, unsigned int n)
{
	unsigned int n;

	for (n = 0; n < n; n++)
		str[n] = byte;
	return (str);
}

/**
 * _memcpy - function that copies memory area
 *
 * @destination: buffer where we will copy to
 * @source: what we are to copy
 * @n: n bytes of @source
 *
 * Return: Always 0 (Success)
*/

char *_memcpy(char *destination, char *source, unsigned int n)
{
	unsigned int n;

	for (n = 0; n < n; n++)
		destination[n] = source[n];
	return (destination);
}

/**
 * _realloc - reallocates a block of memory
 * @pointer: pointer to previous malloc'ated block
 * @my_old_size: byte my_size of previous block
 * @my_new_size: byte my_size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pointer, unsigned int my_old_size, unsigned
int my_new_size)
{
	char *k;

	if (!pointer)
		return (malloc(my_new_size));
	if (!my_new_size)
		return (free(pointer), NULL);
	if (my_new_size == my_old_size)
		return (pointer);

	k = malloc(my_new_size);
	if (!k)
		return (NULL);

	my_old_size = my_old_size < my_new_size ? my_old_size : my_new_size;
	while (my_old_size--)
		k[my_old_size] = ((char *)pointer)[my_old_size];
	free(pointer);
	return (k);
}

/**
 * _calloc - a function that allocates memory
 *
 * @my_nmemb: my_size of array
 * @my_size: my_size of each element
 *
 * Return: pointer with new allocated memory
 *         or NULL if it fails
*/

void *_calloc(unsigned int my_nmemb, unsigned int my_size)
{
	char *k;

	if (my_nmemb == 0 || my_size == 0)
		return (NULL);

	k = malloc(my_nmemb * my_size);
	if (k == NULL)
		return (NULL);

	_memset(k, 0, my_nmemb * my_size);

	return (k);
}
