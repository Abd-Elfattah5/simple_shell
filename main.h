#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <stddef.h>
extern char **environ;

/**
 * struct info - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @argc: lines counter
 * @_environ: environment variable
 */
typedef struct info
{
	char **av;
	char *input;
	char **args;
	int status;
	int argc;
	char **_environ;

} shell_data;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @fun: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	void (*fun)(shell_data *data);
} builtin_t;

void set_data(shell_data *d, char **av);
void _myexit(shell_data *);
void (*_is_builtin(char **av))(shell_data *);

/* cmd_handlers.c */
int _getcmd(char **);
int _execve(shell_data *);
int _parsecmd(shell_data *);

/* string_functions.c */
int _strcmp(const char *s1, const char *s2);
int _strcmp2(const char *s1, const char *s2);
int _strlen(const char *);
int _atoi(char *);

/* env_functions.c */
void _setenv(shell_data *);
void _unsetenv(shell_data *);
char *_concat_all(const char *s1, const char *s2);

void _perror(char *s, shell_data *data, int status);

/* _free.c */
void free_in_buffers(shell_data *);
void free_env(shell_data *);
void free_shell_data(shell_data *);

/* _path.c */
int _pathcheck(shell_data *data);
int parsePATH(char *path, char ***pathtok);
int _concatPATH(char **pathtok, char **concated, char *cmd);
int _strcat(char *s1, char *s2, char **concated);

#endif /* MAIN_H */

