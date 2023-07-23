#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
int _execve(char **argv);
int _parsecmd(char *cmd, char ***argv);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
int _atoi(char *s);
#endif /* MAIN_H */

