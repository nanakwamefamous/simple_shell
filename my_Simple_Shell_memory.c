#include "my_Simple_Shell_shell.h"
/**
 * myfun_bfree - is to frees a pointer and NULLs the address
 * @ptr: is the address of the pointer to free
 *
 * Return: 1 if freed, or 0.
 */
int myfun_bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
