#include "my_Simple_Shell_shell.h"
/**
 * myfun_hsh - is to main shell loop
 *
 * @info: is the parameter & return info struct
 *
 * @av: is the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int myfun_hsh(info_t *info, char **av)
{
	ssize_t u = 0;
	int builtin_ret = 0;

	while (u != -1 && builtin_ret != -2)
	{
		myfun_clear_info(info);
		if (myfun_interactive(info))
			myfun__puts("$ ");
		myfun__eputchar(BUF_FLUSH);
		u = myfun_get_input(info);
		if (u != -1)
		{
			myfun_set_info(info, av);
			builtin_ret = myfun_find_builtin(info);
			if (builtin_ret == -1)
				myfun_find_cmd(info);
		}
		else if (interactive(info))
			myfun__putchar('\n');
		myfun_free_info(info, 0);
	}
	myfun_write_history(info);
	myfun_free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * myfun_find_builtin - is to finds a builtin command
 * @info: is the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed correctly,
 * 1 if builtin found but not correctly executed,
 * 2 if builtin signal an exit() from the process
 */
int myfun_find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", myfun__myexit},
		{"env", myfun__myenv},
		{"help", myfun__myhelp},
		{"history", myfun__myhistory},
		{"setenv", myfun__mysetenv},
		{"unsetenv", myfun__myunsetenv},
		{"cd", myfun__mycd},
		{"alias", myfun__myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (myfun__strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * myfun_find_cmd - is to finds a command in PATH
 * @info: is the parameter & return info struct
 *
 * Return: void or NULL
 */
void myfun_find_cmd(info_t *info)
{
	char *path = NULL;
	int i, p;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, p = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			p++;
	if (!p)
		return;

	path = myfun_find_path(info, myfun__getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		myfun_fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || myfun__getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && myfun_is_cmd(info, info->argv[0]))
			myfun_fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			myfun_print_error(info, "not found\n");
		}
	}
}

/**
 * myfun_fork_cmd - is to forks a an exec thread to run cmd
 * @info: is the parameter & return info struct
 *
 * Return: void or NULL
 */
void myfun_fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, myfun_get_environ(info)) == -1)
		{
			myfun_free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				myfun_print_error(info, "Permission denied\n");
		}
	}
}
