#include "my_Simple_Shell_shell.h"
/**
 * myfun__realloc - is to reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *myfun__realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

/**
 * myfun_ffree - is to frees a string of strings
 * @pp: is a string of strings
 */
void myfun_ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * myfun__memset - is to fills memory with a constant byte
 * @s: is a  pointer to the memory area
 *
 * @b: is a byte to fill *s with
 *
 * @n: is a amount of bytes to be filled
 *
 *
 * Return: pointer to the memory area
 */
char *myfun__memset(char *s, char b, unsigned int n)
{
	unsigned int v;

	for (v = 0; v < n; v++)
		s[v] = b;
	return (s);
}

