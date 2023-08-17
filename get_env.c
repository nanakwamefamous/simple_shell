#include "shell.h"

/**
 * _getenv - Get the value of an environment variable and return its value.
 * @env_name: Name of the environment variable
 *
 * Return: Value of the environment variable, or NULL if it doesn't exist.
 */
char *_getenv(const char *env_name)
{
	char **env_var;
	size_t MY_name_len = _strlen(env_name);

	for (env_var = environ; *env_var != NULL; env_var++)
	{
		if (_strncmp(*env_var, env_name, MY_name_len) == 0 && (*env_var)
			[MY_name_len] == '=')
		{
			return (&(*env_var)[MY_name_len + 1]);
		}
	}

	return (NULL);
}
