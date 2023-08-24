#include "shell.h"

/**
 * bfree - is to frees a pointer and NULLs the address
 * @ptr: is the address of the pointer to free
 *
 * Return: 1 if freed, or 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
