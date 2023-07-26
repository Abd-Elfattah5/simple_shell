#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
extern char **environ;

int parsePATH(char *path, char ***pathtok);
int _execve(char **argv);
int _parsecmd(char *cmd, char ***argv);
char *_pathcheck(char *cmd, char **env);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _strcat(char *s1, char *s2, char **concated);
int _concatPATH(char **pathtok, char **concated, char *cmd);
#endif /* MAIN_H */

