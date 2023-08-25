#include "my_Simple_Shell_shell.h"
/**
 * myfun_get_history_file - is to gets the history file
 *
 * @info: parameter struct
 *
 * Return: to allocated string containg history file
 */

char *myfun_get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = myfun__getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (myfun__strlen(dir) + myfun__strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	myfun__strcpy(buf, dir);
	myfun__strcat(buf, "/");
	myfun__strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * myfun_write_history - is to creates a file,
 * or appends to an existing file
 *
 * @info: is a parameter struct
 *
 * Return: 1 on success, else -1
 */
int myfun_write_history(info_t *info)
{
	ssize_t fd;
	char *filename = myfun_get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		myfun__putsfd(node->str, fd);
		myfun__putfd('\n', fd);
	}
	myfun__putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * myfun_read_history - is to reads history from file
 *
 * @info: is a parameter struct
 *
 * Return: histcount on success, or 0
 */
int myfun_read_history(info_t *info)
{
	int n, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = myfun_get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (n = 0; n < fsize; n++)
		if (buf[n] == '\n')
		{
			buf[n] = 0;
			myfun_build_history_list(info, buf + last, linecount++);
			last = n + 1;
		}
	if (last != n)
		myfun_build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		myfun_delete_node_at_index(&(info->history), 0);
	myfun_renumber_history(info);
	return (info->histcount);
}

/**
 * myfun_build_history_list - is to adds entry to a history linked list
 *
 * @info: Structure containing potential arguments.
 *
 * @buf: is a buffer
 * @linecount: is the history linecount, histcount
 *
 * Return: 0
 */
int myfun_build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	myfun_add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * myfun_renumber_history - is to renumbers the history linked list after changes
 * @info: Structure containing potential arguments.
 *
 * Return: is the new histcount
 */
int myfun_renumber_history(info_t *info)
{
	list_t *node = info->history;
	int n = 0;

	while (node)
	{
		node->num = n++;
		node = node->next;
	}
	return (info->histcount = n);
}
