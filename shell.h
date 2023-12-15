#ifndef _SHELL_H_
#define _SHELL_H_

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"
#define TOK_DELIM " \t\r\n\a\""
extern char **environ;

int _strcmp(char *s1, char *s2);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_read(void);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
int _atoi(char *s);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
int prompt(void);
void _print_num(int n);
char *_strtok(char *str, const char *dlm);
char **split(char *buff);
size_t _strlen(const char *str);
char *_strdup(const char *s);
char *_strcpy(char *des, const char *src);
char *_strcat(char *dstn, char *src);
int _strncmp(const char *s1, const char *s2, size_t n);
int exe_cmd(char **argv);
char *get_path(char *cmd);
char *get_env(const char *nam);
int _env(void);
int _print_str(char *str);
int _putchar(char c);
void check_input(char **splited_input);
int _echoo(char **arg);
char *_con_cat(char *tmp, char **arg, char *tok);
int _PATHstrcmp(const char *s1, const char *s2);
int _proc_fork(char **arg, char *buff, char *fpb);
int _splitPATH(char *str);
char *_pathfbuff(char **arg, char *PATH, char *copy);
int checks(char **arg, char *buff, int exitstat);
void _puts(char *str);
char *_memset(char *s, char b, unsigned int n);
int _splitstring(char *s);
void handle_env_var(char *arg);

/* Alias function */

int _snprint(char *str, size_t size, const char *format, ...);
char *_strncpy(char *dst, const char *src, size_t n);

int _putchar(char c);


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
* struct passinfo - contains all the info to pass to functions
* @arg: the argument string
* @argv: the argument vector
* @path: the PATH string
* @argc: the argument count
* @line_count: the line count
* @err_num: the error number
* @linecount_flag: the linecount flag
* @fname: the file name
* @env: the environment list
* @history: the history list
* @alias: the alias list
* @environ: the environment
* @env_changed: the environment changed flag
* @status: the exit status
* @cmd_buf: the command buffer
* @cmd_buf_type: the command buffer type
* @readfd: the read file descriptor
* @histcount: the history count
*
* Description: the structure to pass to functions
*
* Notes:
* 1. the cmd_buf is a chain buffer, so that it can be freed easily
* 2. the cmd_buf_type is the type of the command in the buffer
* 3. the readfd is the file descriptor to read from
* 4. the histcount is the history count
* 5. the env_changed is the environment changed flag
* 6. the status is the exit status
* 7. the environ is the environment
* 8. the alias is the alias list
* 9. the history is the history list
* 10. the env is the environment list
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}
	builtin_table;


/************************* toem_shloop.c *************************/

int hash(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/************************* toem_parser.c *************************/

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/************************* loophsh.c *************************/

int loophsh(char **);

/************************* toem_errors.c *************************/

void _eputs(char *str);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/************************* toem_string.c *************************/
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/************************* toem_string1.c *************************/
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/************************* toem_exits.c *************************/
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/************************* toem_tokenizer.c *************************/
char **strtow(char *, char *);
char **strtow2(char *, char);

/************************* toem_realloc.c *************************/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/************************* toem_memory.c *************************/
int bfree(void **);

/************************* toem_atoi.c *************************/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/************************* toem_errors1.c *************************/
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/************************* toem_builtin.c *************************/
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/************************* toem_builtin1.c *************************/
int _myhistory(info_t *);
int _myalias(info_t *);

/************************* toem_getline.c *************************/
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t _getline(char** lineptr, size_t* n, FILE* stream);

/************************* toem_getinfo.c *************************/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/************************* toem_environ.c *************************/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/************************* toem_getenv.c *************************/
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/************************* toem_history.c *************************/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/************************* toem_lists.c *************************/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/************************* toem_lists1.c *************************/
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/************************* toem_vars.c *************************/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /* _SHELL_H_ */
