#include "shell.h"

/**
 * input_buf - is to buffers chained commands
 *
 * @info: is a parameter struct
 *
 * @buf: is a address of buffer
 *
 * @len: is a address of len var
 *
 * Return: to return bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t y = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		y = getline(buf, &len_p, stdin);
#else
		y = _getline(info, buf, &len_p);
#endif
		if (y > 0)
		{
			if ((*buf)[y - 1] == '\n')
			{
				(*buf)[y - 1] = '\0';
				y--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = y;
				info->cmd_buf = buf;
			}
		}
	}
	return (y);
}

/**
 * get_input - is to gets a line minus the newline
 *
 * @info: is a parameter struct
 *
 * Return: to return bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t y = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	y = input_buf(info, &buf, &len);
	if (y == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
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
		return (_strlen(p));
	}
	*buf_p = buf;
	return (y);
}

/**
 * read_buf - is to reads a buffer
 * @info: is a parameter struct
 * @buf: is a buffer
 * @i: is a size
 *
 * Return: y
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
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
 * _getline - is to gets the next line of input from STDIN
 * @info: is a parameter struct
 * @ptr: is a address of pointer to buffer, preallocated or NULL
 * @length: is a size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
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

	y = read_buf(info, buf, &len);
	if (y == -1 || (y == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - is to blocks ctrl-C
 *
 * @sig_num: is a signal number
 *
 * Return: be void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
