#include "my_Simple_Shell_shell.h"
/**
 * myfun_list_len - is to determines length of linked list
 * @h: is the pointer to first node
 *
 * Return: should return size of list
 */
size_t myfun_list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * myfun_print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t myfun_print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		myfun__puts(myfun_convert_number(h->num, 10, 0));
		myfun__putchar(':');
		myfun__putchar(' ');
		myfun__puts(h->str ? h->str : "(nil)");
		myfun__puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * myfun_list_to_strings - is to returns an array of strings of the list->str
 * @head: is the pointer to first node
 *
 * Return: the array of strings
 */
char **myfun_list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t n = myfun_list_len(head), o;
	char **strs;
	char *str;

	if (!head || !n)
		return (NULL);
	strs = malloc(sizeof(char *) * (n + 1));
	if (!strs)
		return (NULL);
	for (n = 0; node; node = node->next, n++)
	{
		str = malloc(myfun__strlen(node->str) + 1);
		if (!str)
		{
			for (o = 0; o < n; o++)
				free(strs[o]);
			free(strs);
			return (NULL);
		}

		str = myfun__strcpy(str, node->str);
		strs[n] = str;
	}
	strs[n] = NULL;
	return (strs);
}


/**
 * myfun_node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *myfun_node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = myfun_starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * myfun_get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t myfun_get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
