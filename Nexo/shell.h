#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

void touch(char *name);
void mkdir(char *name);
void ls_wrapper(char *arg);
void pwd_wrapper(char *arg);
void cd(char *name);
void clear_wrapper(char *arg);
void rm(char *name);
void rmdir(char *name, Folder *parent_folder);
void rmdir_wrapper(char *arg);
void cat(char *file);
void echo(char *file, char *container);
void echo_wrapper(char *arg);
void find_wrapper(char *arg);
void finddir_wrapper(char *arg);
void help(char *arg);

#endif
