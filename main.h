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
#endif /* MAIN_H */

