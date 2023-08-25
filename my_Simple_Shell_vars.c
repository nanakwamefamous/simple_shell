#include "my_Simple_Shell_shell.h"
/**
 * myfun_replace_vars - is to replaces vars in the tokenized string
 * @info: is a parameter struct
 *
 * Return: 1 if replaced, or 0
 */
int myfun_replace_vars(info_t *info)
{
	int n = 0;
	list_t *node;

	for (n = 0; info->argv[n]; n++)
	{
		if (info->argv[n][0] != '$' || !info->argv[n][1])
			continue;

		if (!myfun__strcmp(info->argv[n], "$?"))
		{
			myfun_replace_string(&(info->argv[n]),
					myfun__strdup(myfun_convert_number(info->status, 10, 0)));
			continue;
		}
		if (!myfun__strcmp(info->argv[n], "$$"))
		{
			myfun_replace_string(&(info->argv[n]),
					myfun__strdup(myfun_convert_number(getpid(), 10, 0)));
			continue;
		}
		node = myfun_node_starts_with(info->env, &info->argv[n][1], '=');
		if (node)
		{
			myfun_replace_string(&(info->argv[n]),
					myfun__strdup(myfun__strchr(node->str, '=') + 1));
			continue;
		}
		myfun_replace_string(&info->argv[n], myfun__strdup(""));

	}
	return (0);
}



/**
 * myfun_check_chain - is to  checks we should continue chaining
 * based on last status
 * @info: is a parameter struct
 * @buf: is a char buffer
 * @p: is the address of current position in buf
 * @n: is a starting position in buf
 * @len: is a length of buf
 *
 * Return: 0
 */
void myfun_check_chain(info_t *info, char *buf, size_t *p, size_t n, size_t len)
{
	size_t o = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[n] = 0;
			o = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[n] = 0;
			o = len;
		}
	}

	*p = o;
}

/**
 * myfun_replace_alias - is to replaces an aliases in the
 * tokenized string
 * @info: is a parameter struct
 *
 * Return: 1 if replaced, or 0
 */
int myfun_replace_alias(info_t *info)
{
	int n;
	list_t *node;
	char *p;

	for (n = 0; n < 10; n++)
	{
		node = myfun_node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = myfun__strchr(node->str, '=');
		if (!p)
			return (0);
		p = myfun__strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * myfun_is_chain - is to test if current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: is a char buffer
 * @p: is the address of current position in buf
 *
 * Return: 1 if chain delimeter, or  0
 */
int myfun_is_chain(info_t *info, char *buf, size_t *p)
{
	size_t o = *p;

	if (buf[o] == '|' && buf[o + 1] == '|')
	{
		buf[o] = 0;
		o++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[o] == '&' && buf[o + 1] == '&')
	{
		buf[o] = 0;
		o++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[o] == ';')
	{
		buf[o] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = o;
	return (1);
}

/**
 * myfun_replace_string - is to replaces string
 * @old: is a address of old string
 * @new: is a new string
 *
 * Return: 1 if replaced, or 0
 */
int myfun_replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
