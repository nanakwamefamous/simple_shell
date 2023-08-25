#include "my_Simple_Shell_shell.h"
/**
 * main - is to entry point
 * @ac: is the arg count
 * @av: is the arg vector
 *
 * Return: 0 on success, or 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int op = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (op)
			: "r" (op));

	if (ac == 2)
	{
		op = open(av[1], O_RDONLY);
		if (op == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				myfun__eputs(av[0]);
				myfun__eputs(": 0: Can't open ");
				myfun__eputs(av[1]);
				myfun__eputchar('\n');
				myfun__eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = op;
	}
	myfun_populate_env_list(info);
	read_history(info);
	myfun_hsh(info, av);
	return (EXIT_SUCCESS);
}
