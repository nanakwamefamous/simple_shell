#include "my_Simple_Shell_shell.h"
/**
 * myfun_get_environ - is to returns the string array copy of our environ
 *
 * @info: is a Structure containing potential arguments.
 *
 * function prototype.
 *
 * Return: 0
 */
char **myfun_get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = myfun_list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * myfun__unsetenv - is to Remove an environment variable
 *
 * @var: the string env var property
 * @info: is a Structure containing potential arguments.
 *
 * function prototype.
 *  Return: 1 on delete, or 0

 */
int myfun__unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t n = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = myfun_starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = myfun_delete_node_at_index(&(info->env), n);
			n = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		n++;
	}
	return (info->env_changed);
}

/**
 * myfun__setenv - is to Initialize a new environment variable,
 * or modify an existing one
 *
 * @info: Structure containing potential arguments.
 * function prototype.
 * @var: is a string env var property
 * @value: is a string env var value
 *  Return: 0
 */
int myfun__setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(myfun__strlen(var) + myfun__strlen(value) + 2);
	if (!buf)
		return (1);
	myfun__strcpy(buf, var);
	myfun__strcat(buf, "=");
	myfun__strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = myfun_starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	myfun_add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
