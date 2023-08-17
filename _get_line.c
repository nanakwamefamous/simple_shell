#include "shell.h"

/*
 * get_line - is to read input from the standard input.
 * Return: string entered by the user.
*/
void *get_line(void)
{
	static char MY_buffer[BUFFER_SIZE];
	static int MY_buf_pos, MY_buf_size;
	char *input_string = NULL;
	char MY_current_char;
	int MY_input_len = 0;

	while (1)
	{
		if (MY_buf_pos >= MY_buf_size)
		{
			MY_buf_size = read(STDIN_FILENO, MY_buffer, BUFFER_SIZE);
			MY_buf_pos = 0;
			if (MY_buf_size == 0)
				return (input_string);
			else if (MY_buf_size < 0)
			{
				perror("read");
				return (NULL);
			}
		}

		MY_current_char = MY_buffer[MY_buf_pos];

		MY_buf_pos++;

		if (MY_current_char == '\n')
		{
			input_string = realloc(input_string, MY_input_len + 1);
			input_string[MY_input_len] = '\0';
			return (input_string);
		}
		else
		{
			input_string = realloc(input_string, MY_input_len + 1);
			input_string[MY_input_len] = MY_current_char;
			MY_input_len++;
		}
	}
}
