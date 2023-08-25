#include "my_Simple_Shell_shell.h"

/**
 * myfun_populate_env_list - is to populates env linked list myfun_
 * @info: Structure containing potential arguments.
 *
 *
 * function prototype
 *
 * Return: 0
 */
int myfun_populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t n;

	for (n = 0; environ[n]; n++)
		myfun_add_node_end(&node, environ[n], 0);
	info->env = node;
	return (0);
}

/**
 * myfun__myunsetenv - is to Remove an environment variable
 *
 * @info: Structure containing potential arguments.
 *
 * constant function prototype
 *
 * Return: 0
 */
int myfun__myunsetenv(info_t *info)
{
	int n;

	if (info->argc == 1)
	{
		myfun__eputs("Too few arguements.\n");
		return (1);
	}
	for (n = 1; n <= info->argc; n++)
		myfun__unsetenv(info, info->argv[n]);

	return (0);
}

/**
 * myfun__getenv - is to gets the value of an environ variable
 *
 * @info: Structure containing potential arguments.
 *
 * @name: env var name
 *
 * Return: value
 */
char *myfun__getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = myfun_starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * myfun__mysetenv - is to Initialize a new environment variable,
 * / modify an existing one
 * @info: Structure containing potential arguments.
 *
 * function prototype.
 *  Return: 0
 */
int myfun__mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		myfun__eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (myfun__setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}



/**
 * myfun__myenv - is to prints the current environment
 *
 * @info: Structure containing potential arguments.
 *
 * function prototype.
 *
 * Return: Always 0
 */
int myfun__myenv(info_t *info)
{
	myfun_print_list_str(info->env);
	return (0);
}
