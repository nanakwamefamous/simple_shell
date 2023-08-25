#include "my_Simple_Shell_shell.h"
/**
 * **myfun_strtow - is to splits a string into words.
 * @str: is a input string
 * @d: is a delimeter string
 * Return: NULL on failure
 */

char **myfun_strtow(char *str, char *d)
{
	int n, z, o, p, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (n = 0; str[n] != '\0'; n++)
		if (!is_delim(str[n], d) && (is_delim(str[n + 1], d) || !str[n + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, z = 0; z < numwords; z++)
	{
		while (is_delim(str[n], d))
			n++;
		o = 0;
		while (!is_delim(str[n + o], d) && str[n + o])
			o++;
		s[z] = malloc((o + 1) * sizeof(char));
		if (!s[z])
		{
			for (o = 0; o < z; o++)
				free(s[o]);
			free(s);
			return (NULL);
		}
		for (p = 0; p < o; p++)
			s[z][p] = str[n++];
		s[z][p] = 0;
	}
	s[z] = NULL;
	return (s);
}

/**
 * **myfun_strtow2 - is to splits a string into words
 * @str: is a input string
 * @d: is a delimeter
 * Return: NULL on failure
 */
char **myfun_strtow2(char *str, char d)
{
	int n, z, o, p, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (n = 0; str[n] != '\0'; n++)
		if ((str[n] != d && str[n + 1] == d) ||
				    (str[n] != d && !str[n + 1]) || str[n + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (n = 0, z = 0; z < numwords; z++)
	{
		while (str[n] == d && str[n] != d)
			n++;
		o = 0;
		while (str[n + o] != d && str[n + o] && str[n + o] != d)
			o++;
		s[z] = malloc((o + 1) * sizeof(char));
		if (!s[z])
		{
			for (o = 0; o < z; o++)
				free(s[o]);
			free(s);
			return (NULL);
		}
		for (p = 0; p < o; p++)
			s[z][p] = str[n++];
		s[z][p] = 0;
	}
	s[z] = NULL;
	return (s);
}
