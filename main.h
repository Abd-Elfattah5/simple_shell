#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
extern char **environ;

int parsePATH(char *path, char ***pathtok);
int _execve(char **argv);
int _parsecmd(char *cmd, char ***argv);
char *_pathcheck(char *cmd, char **env);
#endif /* MAIN_H */

