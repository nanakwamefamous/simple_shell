#include "my_Simple_Shell_shell.h"

/**
 * myfun_unset_alias - is to sets alias to string
 * @info: is parameter struct
 * @str: is  string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int myfun_unset_alias(info_t *info, char *str)
{
	char *p, o;
	int ret;

	p = myfun__strchr(str, '=');
	if (!p)
		return (1);
	o = *p;
	*p = 0;
	ret = myfun_delete_node_at_index(&(info->alias),
		myfun_get_node_index(info->alias, myfun_node_starts_with(info->alias, str, -1)));
	*p = o;
	return (ret);
}

/**
 * print_alias - is to prints an alias string
 * @node: is alias node
 *
 * Return: 0 on success, or 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = myfun__strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		myfun__putchar(*a);
		myfun__putchar('\'');
		myfun__puts(p + 1);
		myfun__puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * myfun__myhistory - is to displays the history list,
 * with line numbers and starting at 0.
 * @info: Structure containing potential arguments.
 * function prototype.
 *  Return: Always 0
 */
int myfun__myhistory(info_t *info)
{
	myfun_print_list(info->history);
	return (0);
}

/**
 * set_alias - sets alias to string
 * @info: is a parameter struct
 * @str: is a string alias
 *
 * Return: 0 on success, or 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = myfun__strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (myfun_unset_alias(info, str));

	myfun_unset_alias(info, str);
	return (myfun_add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * myfun__myalias - is to mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * function prototype.
 * Return: 0
 */
int myfun__myalias(info_t *info)
{
	int u = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (u = 1; info->argv[u]; u++)
	{
		p = myfun__strchr(info->argv[u], '=');
		if (p)
			set_alias(info, info->argv[u]);
		else
			print_alias(myfun_node_starts_with(info->alias, info->argv[u], '='));
	}

	return (0);
}
