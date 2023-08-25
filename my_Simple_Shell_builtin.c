#include "my_Simple_Shell_shell.h"

/**
 * myfun__myexit - is to exits the shell
 * @info: is Structure containing potential arguments.
 *
 * Return: is to exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int myfun__myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = myfun__erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			myfun_print_error(info, "Illegal number: ");
			myfun__eputs(info->argv[1]);
			myfun__eputchar('\n');
			return (1);
		}
		info->err_num = myfun__erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * myfun__mycd - is to changes the current directory of the process
 * @info: Structure containing potential arguments.
 *
 *
 * Return 0
 */
int myfun__mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		myfun__puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = myfun__getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = myfun__getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (myfun__strcmp(info->argv[1], "-") == 0)
	{
		if (!myfun__getenv(info, "OLDPWD="))
		{
			myfun__puts(s);
			myfun__putchar('\n');
			return (1);
		}
		myfun__puts(myfun__getenv(info, "OLDPWD=")), myfun__putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = myfun__getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		myfun_print_error(info, "can't cd to ");
		myfun__eputs(info->argv[1]), myfun__eputchar('\n');
	}
	else
	{
		myfun__setenv(info, "OLDPWD", myfun__getenv(info, "PWD="));
		myfun__setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - is to changes the current directory of the process
 * @info: is to Structure containing potential arguments.
 *
 *
 * function prototype
 * Return: Always 0
 */
int myfun__myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	myfun__puts("help call works. Function not yet implemented \n");
	if (0)
		myfun__puts(*arg_array); /* this temp att_unused workaround */
	return (0);
}
