#include "my_Simple_Shell_shell.h"
/**
 * myfun_input_buf - is to buffers chained commands
 *
 * @info: is a parameter struct
 *
 * @buf: is a address of buffer
 *
 * @len: is a address of len var
 *
 * Return: to return bytes read
 */
ssize_t myfun_input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, myfun_sigintHandler);
#if USE_GETLINE
		y = getline(buf, &len_p, stdin);
#else
		y = myfun__getline(info, buf, &len_p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0';
				y--;
			}
			info->linecount_flag = 1;
			myfun_remove_comments(*buf);
			myfun_build_history_list(info, *buf, info->histcount++);
			{
				*len = y;
				info->cmd_buf = buf;
			}
		}
	}
	return (y);
}

/**
 * myfun_get_input - is to gets a line minus the newline
 *
 * @info: is a parameter struct
 *
 * Return: to return bytes read
 */
ssize_t myfun_get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t y = 0;
	char **buf_p = &(info->arg), *p;

	myfun__putchar(BUF_FLUSH);
	y = myfun_input_buf(info, &buf, &len);
	if (y == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		myfun_check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (myfun_is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (myfun__strlen(p));
	}
	*buf_p = buf;
	return (y);
}

/**
 * myfun_read_buf - is to reads a buffer
 * @info: is a parameter struct
 * @buf: is a buffer
 * @i: is a size
 *
 * Return: y
 */
ssize_t myfun_read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t y = 0;

	if (*i)
		return (0);
	y = read(info->readfd, buf, READ_BUF_SIZE);
	if (y >= 0)
		*i = y;
	return (y);
}

/**
 * myfun__getline - is to gets the next line of input from STDIN
 * @info: is a parameter struct
 * @ptr: is a address of pointer to buffer, preallocated or NULL
 * @length: is a size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int myfun__getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t y = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	y = myfun_read_buf(info, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = myfun__strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = myfun__realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		myfun__strncat(new_p, buf + i, k - i);
	else
		myfun__strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * myfun_sigintHandler - is to blocks ctrl-C
 *
 * @sig_num: is a signal number
 *
 * Return: be void
 */
void myfun_sigintHandler(__attribute__((unused))int sig_num)
{
	myfun__puts("\n");
	myfun__puts("$ ");
	myfun__putchar(BUF_FLUSH);
}
