#include "shell.h"

/**
 * execute - is to Execute a command with arguments.
 * @args_array: An array of arguments to execute
 *
 * Return: status of the command
 */
int execute(char **args_array)
{
	pid_t IDs;
	int MY_status = 0;
	char *command_path, *MY_envp[2];

	if (args_array == NULL || *args_array == NULL)
		return (MY_status);
	if (check_for_builtin(args_array))
		return (MY_status);

	IDs = fork();
	if (IDs < 0)
	{
		_puterror("fork");
		return (1);
	}
	if (IDs == -1)
		perror(args_array[0]), free_tokens(args_array), free_last_input();
	if (IDs == 0)
	{
		MY_envp[0] = get_path();
		MY_envp[1] = NULL;
		command_path = NULL;
		if (args_array[0][0] != '/')
			command_path = find_in_path(args_array[0]);
		if (command_path == NULL)
			command_path = args_array[0];
		if (execve(command_path, args_array, MY_envp) == -1)
		{
			perror(args_array[0]), free_tokens(args_array), free_last_input();
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(IDs, &MY_status, WUNTRACED);
		} while (!WIFEXITED(MY_status) && !WIFSIGNALED(MY_status));
	}
	return (MY_status);
}
