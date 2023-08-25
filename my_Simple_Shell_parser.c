#include "my_Simple_Shell_shell.h"
/**
 * myfun_find_path - is to finds this cmd in the PATH string
 * @info: is the info struct
 * @pathstr: is the PATH string
 * @cmd: is the cmd to find
 *
 * Return: NULL
 */
char *myfun_find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((myfun__strlen(cmd) > 2) && myfun_starts_with(cmd, "./"))
	{
		if (myfun_is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = myfun_dup_chars(pathstr, curr_pos, n);
			if (!*path)
				myfun__strcat(path, cmd);
			else
			{
				myfun__strcat(path, "/");
				myfun__strcat(path, cmd);
			}
			if (myfun_is_cmd(info, path))
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
 * myfun_is_cmd - is to determines if a file is an executable command
 *
 * @info: is the info struct
 *
 * @path: is the path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int myfun_is_cmd(info_t *info, char *path)
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
 * myfun_dup_chars - is to duplicates characters
 * @pathstr: is a PATH string
 * @start: is a starting index
 * @stop: is a stopping index
 *
 * Return: the pointer to new buffer
 */
char *myfun_dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int n = 0, o = 0;

	for (o = 0, n = start; n < stop; n++)
		if (pathstr[n] != ':')
			buf[o++] = pathstr[n];
	buf[o] = 0;
	return (buf);
}

