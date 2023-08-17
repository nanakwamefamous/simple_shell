#include "shell.h"

/**
 * find_in_path - Looks for a command in each directory
 *
 * @cmd:  `command` string to look for.
 *
 * Return: the full path (success) if it is found, or NULL if it is not 
 * found (failure).
*/
char *find_in_path(char *cmd)
{
	struct stat MY_st;
	int MY_stat_ret, n;
	char MY_buf[PATH_MAX_LENGTH], *MY_path, *MY_ret, **MY_dir;

	MY_path = get_path();
	if (!MY_path)
		return (NULL);
	MY_dir = tokenize(MY_path, PATH_SEPARATOR);
	if (!MY_dir)
		return (NULL);
	for (n = 0; MY_dir[n]; n++)
	{
		_memset(MY_buf, 0, PATH_MAX_LENGTH);
		_strcpy(MY_buf, MY_dir[n]);
		_strcat(MY_buf, "/");
		_strcat(MY_buf, cmd);
		MY_stat_ret = stat(MY_buf, &MY_st);
		if (MY_stat_ret == 0 && S_ISREG(MY_st.st_mode) && (MY_st.st_mode & S_IXUSR))
		{
			free_tokens(MY_dir);
			MY_ret = malloc(sizeof(char) * (strlen(MY_buf) + 1));
			if (!MY_ret)
				return (NULL);
			strcpy(MY_ret, MY_buf);
			return (MY_ret);
		}
	}
	if (MY_stat_ret == -1)
		free_tokens(MY_dir);
	return (NULL);
}
