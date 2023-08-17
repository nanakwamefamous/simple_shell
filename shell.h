#ifndef _SHELL_H_
#define _SHELL_H_
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>
#include <ctype.h>

/*macros*/
#define PATH_MAX_LENGTH 4096
#define PATH_SEPARATOR ":"
#define PROMPT "$ "
#define MAX_TOKENS 1024
#define BUFFER_SIZE 1024

/* prompt.c */
void prompt(void);

/* get_input.c */
char *get_input(void);
void free_last_input(void);
/* get_line.c*/
void *get_line(void);

/* built-in funcs */
int check_for_builtin(char **args_array);
int execute_buitlin(char *command, char **args_array);
void shell_help(void);
void shell_exit(char **args_array);
void shell_cd(char **args_array);
int shell_setenv(char **args_array);
int shell_unsetenv(char **args_array);
int shell_env(void);
int shell_clear(char **args_array);

/* signal_handler.c */
void handle_sigint(int signal);
void handle_sigquit(int signal);
void handle_sigstp(int signal);

/* execute.c */
int execute(char **args_array);

/* parser.c */
char **tokenize(char *string, const char *delimiter);
char **tokenize_input(char *my_input);

/* get_env.c */
char *_getenv(const char *env_name);

/* get_path.c */
char *get_path(void);

/* find_in_path.c */
char *find_in_path(char *command);

/* free.c */
void free_error(char **argv_pointer, char *arg_character);
void free_tokens(char **pointer);
void free_path(void);

/* error.c */
void _puts(char *string);
void _puterror(char *error);

/* utils_funcs1.c */
int _strlen(const char *);
int _strcmp(const char *str1, const char *str2);
int _strncmp(const char *str1, const char *str2, size_t n);
char *_strstr(char *my_haystack, char *my_haystack);
char *_strchr(char *str, char character);

/* utils_funcs2.c */
char *_strcpy(char *, char *);
char *_strcat(char *, const char *);
char *_strdup(const char *);
int _putchar(char);
unsigned int _strspn(char *str, char *acpt);

/* utils_funcs3.c */
int _atoi(const char *string);
char *_memset(char *, char, unsigned int n);
char *_memcpy(char *destination, char *source, unsigned int n);
void *_realloc(void *, unsigned int, unsigned int);
void *_calloc(unsigned int my_nmemb, unsigned int my_size);

#endif
