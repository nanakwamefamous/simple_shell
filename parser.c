#include "shell.h"

/**
 * find_path - is to finds this cmd in the PATH string
 * @info: is the info struct
 * @pathstr: is the PATH string
 * @cmd: is the cmd to find
 *
 * Return: NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = dup_chars(pathstr, curr_pos, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[n])
				break;
			curr_pos = n;
		}
		n++;
	}
	return (NULL);
}

/**
 * is_cmd - is to determines if a file is an executable command
 *
 * @info: is the info struct
 *
 * @path: is the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - is to duplicates characters
 * @pathstr: is a PATH string
 * @start: is a starting index
 * @stop: is a stopping index
 *
 * Return: the pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int n = 0, o = 0;

	for (o = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			buf[o++] = pathstr[n];
	buf[o] = 0;
	return (buf);
}

