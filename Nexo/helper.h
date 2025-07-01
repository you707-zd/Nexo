#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdbool.h>

typedef struct Folder Folder;

typedef struct {
    char *filename;
    FILE *name;
    Folder *parent;
} TreeFile;

typedef struct Folder {
    char *name;
    struct Folder *parent;
    struct Folder *children[100];
    TreeFile *file_children[100];
    int file_children_count;
    int children_count;
    bool name_allocated;
} Folder;

typedef struct {
    char *cmd;
    void (*func)(char *arg);
} Command;

extern Folder *pwd;

char *get_string(char *prompt);
int get_int(char *prompt);
int separator(char *input, char *words[100]);
void free_tree(Folder *home);
bool validate_input(char *cmd, int words_count);

#endif
