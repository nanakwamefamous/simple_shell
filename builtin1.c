#include "shell.h"

/**
 * unset_alias - is to sets alias to string
 * @info: is parameter struct
 * @str: is  string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, o;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	o = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
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
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myhistory - is to displays the history list,
 * with line numbers and starting at 0.
 * @info: Structure containing potential arguments.
 * function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
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

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * _myalias - is to mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * function prototype.
 * Return: 0
 */
int _myalias(info_t *info)
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
		p = _strchr(info->argv[u], '=');
		if (p)
			set_alias(info, info->argv[u]);
		else
			print_alias(node_starts_with(info->alias, info->argv[u], '='));
	}

	return (0);
}
