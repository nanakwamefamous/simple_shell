#include "my_Simple_Shell_shell.h"
/**
 * myfun_clear_info - is to initializes info_t struct
 * @info: is a struct address
 */
void myfun_clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * myfun_set_info - is to initializes info_t struct
 * @info: is a struct address
 * @av: is a argument vector
 */
void myfun_set_info(info_t *info, char **av)
{
	int n = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = myfun_strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = myfun__strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (n = 0; info->argv && info->argv[n]; n++)
			;
		info->argc = n;

		myfun_replace_alias(info);
		myfun_replace_vars(info);
	}
}

/**
 * myfun_free_info - is to frees info_t struct fields
 * @info: is a struct address
 * @all: is a true if freeing all fields
 */
void myfun_free_info(info_t *info, int all)
{
	myfun_ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			myfun_free_list(&(info->env));
		if (info->history)
			myfun_free_list(&(info->history));
		if (info->alias)
			myfun_free_list(&(info->alias));
		myfun_ffree(info->environ);
			info->environ = NULL;
		myfun_bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		myfun__putchar(BUF_FLUSH);
	}
}
