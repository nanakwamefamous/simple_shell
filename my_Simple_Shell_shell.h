#ifndef _SHELL_H_
#define _SHELL_H_

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

/* for/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* myfun_convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: is the number field
 * @str: is a string
 * @next: is the points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - is to contains pseudo-arguements to
 * pass into a function,allowing uniform prototype for
 * function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv: array of strings generated from arg
 * @path: string path for the current command
 * @environ: custom modified copy of environ from LL env
 * @history: history node
 * @alias: alias node
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @status: return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @env_changed: on if environ was changed
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: builtin command flag
 * @func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* Represent_my_Simple_Shell_loop.c */
int myfun_hsh(info_t *, char **);
int myfun_find_builtin(info_t *);
void myfun_find_cmd(info_t *);
void myfun_fork_cmd(info_t *);

/* Represent_my_Simple_Shell_parser.c */
int myfun_is_cmd(info_t *, char *);
char *myfun_dup_chars(char *, int, int);
char *myfun_find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* Represent_my_Simple_Shell_errors.c */
void myfun__eputs(char *);
int myfun__eputchar(char);
int myfun__putfd(char c, int fd);
int myfun__putsfd(char *str, int fd);

/* Represent_my_Simple_Shell_string.c */
int myfun__strlen(char *);
int myfun__strcmp(char *, char *);
char *myfun_starts_with(const char *, const char *);
char *myfun__strcat(char *, char *);

/* Represent_my_Simple_Shell_string1.c */
char *myfun__strcpy(char *, char *);
char *myfun__strdup(const char *);
void myfun__puts(char *);
int myfun__putchar(char);

/* Represent_my_Simple_Shell_exits.c */
char *myfun__strncpy(char *, char *, int);
char *myfun__strncat(char *, char *, int);
char *myfun__strchr(char *, char);

/* Represent_my_Simple_Shell_tokenizer.c */
char **myfun_strtow(char *, char *);
char **myfun_strtow2(char *, char);

/* Represent_my_Simple_Shell_realloc.c */
char *myfun__memset(char *, char, unsigned int);
void myfun_ffree(char **);
void *myfun__realloc(void *, unsigned int, unsigned int);

/* Represent_my_Simple_Shell_memory.c */
int myfun_bfree(void **);

/* Represent_my_Simple_Shell_atoi.c */
int myfun_interactive(info_t *);
int myfun_is_delim(char, char *);
int myfun__isalpha(int);
int myfun__atoi(char *);

/* Represent_my_Simple_Shell_errors1.c */
int myfun__erratoi(char *);
void myfun_print_error(info_t *, char *);
int myfun_print_d(int, int);
char *myfun_convert_number(long int, int, int);
void myfun_remove_comments(char *);

/* Represent_my_Simple_Shell_builtin.c */
int myfun__myexit(info_t *);
int myfun__mycd(info_t *);
int myfun__myhelp(info_t *);

/* Represent_my_Simple_Shell_builtin1.c */
int myfun__myhistory(info_t *);
int myfun__myalias(info_t *);

/*Represent_my_Simple_Shell_getline.c */
ssize_t myfun_get_input(info_t *);
int myfun__getline(info_t *, char **, size_t *);
void myfun_sigintHandler(int);

/* Represent_my_Simple_Shell_getinfo.c */
void myfun_clear_info(info_t *);
void myfun_set_info(info_t *, char **);
void myfun_free_info(info_t *, int);

/* Represent_my_Simple_Shell_environ.c */
char *myfun__getenv(info_t *, const char *);
int myfun__myenv(info_t *);
int myfun__mysetenv(info_t *);
int myfun__myunsetenv(info_t *);
int myfun_populate_env_list(info_t *);

/* Represent_my_Simple_Shell_getenv.c */
char **myfun_get_environ(info_t *);
int myfun__unsetenv(info_t *, char *);
int myfun__setenv(info_t *, char *, char *);

/* Represent_my_Simple_Shell_history.c */
char *myfun_get_history_file(info_t *info);
int myfun_write_history(info_t *info);
int myfun_read_history(info_t *info);
int myfun_build_history_list(info_t *info, char *buf, int linecount);
int myfun_renumber_history(info_t *info);

/* Represent_my_Simple_Shell_lists.c */
list_t *myfun_add_node(list_t **, const char *, int);
list_t *myfun_add_node_end(list_t **, const char *, int);
size_t myfun_print_list_str(const list_t *);
int myfun_delete_node_at_index(list_t **, unsigned int);
void myfun_free_list(list_t **);

/* Represent_my_Simple_Shell_lists1.c */
size_t myfun_list_len(const list_t *);
char **myfun_list_to_strings(list_t *);
size_t myfun_print_list(const list_t *);
list_t *myfun_node_starts_with(list_t *, char *, char);
ssize_t myfun_get_node_index(list_t *, list_t *);

/* Represent_my_Simple_Shell_vars.c */
int myfun_is_chain(info_t *, char *, size_t *);
void myfun_check_chain(info_t *, char *, size_t *, size_t, size_t);
int myfun_replace_alias(info_t *);
int myfun_replace_vars(info_t *);
int myfun_replace_string(char **, char *);

#endif