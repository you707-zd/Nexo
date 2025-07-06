#include <ctype.h>
#include "helper.h"
#include "shell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_file(char *file, Folder *current_folder, bool *found)
{
    if (*found) return;

    for (int i = 0; i < current_folder->file_children_count; i++)
    {
        if (strcmp(file, current_folder->file_children[i]->filename) == 0)
        {
            *found = true;
            return;
        }
    }

    for (int i = 0; i < current_folder->children_count; i++)
    {
        find_file(file, current_folder->children[i], found);
    }
}

Folder *root(Folder *mark)
{
    if (mark->parent == NULL)
    {
        return mark;
    }

    return root(mark->parent);
}

void touch(char *name)
{
    for (int i = 0; i < pwd->file_children_count; i++)
    {
        if (strcmp(name, pwd->file_children[i]->filename) == 0)
        {
            printf("File already exists.\n");
            return;
        }
    }

    Folder *temp = root(pwd);
    bool found = false;
    find_file(name, temp, &found);

    if (found)
    {
        printf("Sorry, There is already a file with this exact name in your OS :(\n");
        return;
    }

    TreeFile *file_intended = calloc(1, sizeof(TreeFile));
    file_intended->parent = pwd;
    file_intended->filename = strdup(name);
    pwd->file_children[pwd->file_children_count++] = file_intended;

    file_intended->name = fopen(name, "w");
    if (file_intended->name == NULL)
    {
        printf("Couldn't create the file.\n");
        free(file_intended->filename);
        free(file_intended);
        return;
    }

    printf("File created successfully.\n");
    fclose(file_intended->name);
}

void mkdir(char *name)
{
    for (int i = 0; i < pwd->children_count; i++)
    {
        if (strcmp(pwd->children[i]->name, name) == 0)
        {
            printf("Folder already exists.\n");
            return;
        }
    }
    Folder *new = calloc(1, sizeof(Folder));
    new->name = strdup(name);
    new->name_allocated = true;
    new->parent = pwd;
    pwd->children[pwd->children_count++] = new;
}

void ls(void)
{
    for (int i = 0; i < pwd->children_count; i++)
    {
        Folder *temp = pwd->children[i];
        printf("%s/\t", temp->name);
    }

    for (int i = 0; i < pwd->file_children_count; i++)
    {
        TreeFile *temp = pwd->file_children[i];
        printf("%s\t", temp->filename);
    }

    printf("\n");
}

void cwd(Folder *current_directory)
{
    if (current_directory->parent == NULL)
    {
        printf("/");
        return;
    }

    Folder *temp = current_directory->parent;
    cwd(temp);
    printf("%s/", current_directory->name);
}

void cd(char *name)
{
    bool indicator = false;
    int i = 0;
    while (i < pwd->children_count)
    {
        if (strcmp(pwd->children[i]->name, name) == 0)
        {
            indicator = true;
            break;
        }

        i++;
    }

    if (!indicator)
    {
        printf("There is no such folder!!\n");
        return;
    }

    Folder *temp = pwd->children[i];
    pwd = temp;
}

void clear(void)
{
    printf("\033[2J\033[H");
    fflush(stdout);
}

void rm(char *name)
{
    bool indicator = false;
    int i = 0;
    while (i < pwd->file_children_count)
    {
        if (strcmp(pwd->file_children[i]->filename, name) == 0)
        {
            indicator = true;
            break;
        }

        i++;
    }

    if (!indicator)
    {
        printf("There is no such file!!\n");
        return;
    }

    char *confirmation = get_string("Do you really want to delete this file? ");
    if (strcasecmp(confirmation, "yes") == 0 || tolower(confirmation[0]) == 'y')
    {
        remove(pwd->file_children[i]->filename);
        free(pwd->file_children[i]->filename);
        free(pwd->file_children[i]);

        for (int j = i; j < pwd->file_children_count - 1; j++)
        {
            pwd->file_children[j] = pwd->file_children[j + 1];
        }
        pwd->file_children[pwd->file_children_count - 1] = NULL;
        pwd->file_children_count--;
        return;
    }

    return;
}

void rmdir(char *name, Folder *parent_folder)
{
    bool indicator = false;
    int i = 0;
    while (i < parent_folder->children_count)
    {
        if (parent_folder->children[i] != NULL && strcmp(parent_folder->children[i]->name, name) == 0)
        {
            indicator = true;
            break;
        }

        i++;
    }

    if (!indicator)
    {
        printf("There is no such folder!!\n");
        return;
    }

    Folder *target = parent_folder->children[i];
    for (int j = 0; j < target->children_count; j++)
    {
        if (target->children[j] != NULL)
        {
            rmdir(target->children[j]->name, target);
        }
    }

    while (target->file_children_count > 0)
    {
        // delete index 0
        remove(target->file_children[0]->filename);
        free(target->file_children[0]->filename);
        free(target->file_children[0]);

        // shift remaining file pointers
        for (int j = 0; j < target->file_children_count - 1; j++)
        {
            target->file_children[j] = target->file_children[j + 1];
        }

        target->file_children[target->file_children_count - 1] = NULL;
        target->file_children_count--;
    }

    for (int y = i; y < parent_folder->children_count - 1; y++)
    {
        parent_folder->children[y] = parent_folder->children[y + 1];
    }

    parent_folder->children[parent_folder->children_count - 1] = NULL;
    parent_folder->children_count--;

    if (target->name_allocated)
    {
        free(target->name);
    }

    free(target);
}

bool rmdir_confirmation(void)
{
    while (1)
    {
        char *confirmation = get_string("Do you really want to delete this directory? (y/n): ");

        if (strcasecmp(confirmation, "yes") == 0 || strcasecmp(confirmation, "y") == 0)
        {
            free(confirmation);
            return true;
        }
        else if (strcasecmp(confirmation, "no") == 0 || strcasecmp(confirmation, "n") == 0)
        {
            free(confirmation);
            return false;
        }

        printf("Invalid input. Please enter 'y' or 'n'.\n");
        free(confirmation);
    }
}

void cat(char *file)
{
    bool indicator = false;
    int i = 0;
    while (i < pwd->file_children_count)
    {
        if (strcmp(pwd->file_children[i]->filename, file) == 0)
        {
            indicator = true;
            break;
        }

        i++;
    }

    if (!indicator)
    {
        printf("There is no such file!!\n");
        return;
    }

    FILE *file_input = fopen(file, "r");
    if (!file_input)
    {
        printf("Failed to open the file.\n");
        return;
    }

    char buffer[1024];
    size_t n;
    while ((n = fread(buffer, sizeof(char), sizeof(buffer), file_input)) > 0)
    {
        fwrite(buffer, sizeof(char), n, stdout);
    }

    fclose(file_input);
}

void echo(char *file, char *container)
{
    bool indicator = false;
    int i = 0;
    while (i < pwd->file_children_count)
    {
        if (strcmp(pwd->file_children[i]->filename, file) == 0)
        {
            indicator = true;
            break;
        }

        i++;
    }

    if (!indicator)
    {
        printf("There is no such file!!\n");
        return;
    }

    char *content = NULL;
    if (container == NULL)
    {
        content = get_string("Enter Input: ");
    }

    FILE *file_output = fopen(file, "w");
    if (!file_output)
    {
        printf("Failed to open the file.\n");
        free(content);
        return;
    }

    if (content == NULL)
    {
        fprintf(file_output, "%s\n", container);
    }
    else
    {
        fprintf(file_output, "%s\n", content);
        free(content);
    }

    fclose(file_output);
    printf("Written to file successfully.\n");
}

void find(char *file, Folder *current_folder, bool *found)
{
    if (*found) return;

    for (int i = 0; i < current_folder->file_children_count; i++)
    {
        if (strcmp(file, current_folder->file_children[i]->filename) == 0)
        {
            cwd(current_folder);
            printf("\n");
            *found = true;
            return;
        }
    }

    for (int i = 0; i < current_folder->children_count; i++)
    {
        find(file, current_folder->children[i], found);
    }
}

void finddir(char *name, Folder *current_folder, bool *found)
{
    if (*found) return;

    for (int i = 0; i < current_folder->children_count; i++)
    {
        if (strcmp(name, current_folder->children[i]->name) == 0)
        {
            cwd(current_folder);
            printf("\n");
            *found = true;
            return;
        }

        finddir(name, current_folder->children[i], found);
    }
}

void pwd_wrapper(char *arg)
{
    (void)arg;
    cwd(pwd);
}

void ls_wrapper(char *arg)
{
    (void)arg;
    ls();
}

void clear_wrapper(char *arg)
{
    (void)arg;
    clear();
}

void rmdir_wrapper(char *arg)
{
    if (rmdir_confirmation()) rmdir(arg, pwd);
}

void echo_wrapper(char *arg)
{
    echo(arg, NULL);
}

void find_wrapper(char *arg)
{
    bool found = false;
    find(arg, pwd, &found);

    if (!found)
    {
        printf("There's no such file!!\n");
    }
}

void finddir_wrapper(char *arg)
{
    bool found = false;
    finddir(arg, pwd, &found);

    if (!found)
    {
        printf("There's no such folder!!\n");
    }
}

void help(char *arg)
{
    (void)arg;

    printf("nexo Command Guide:\n");
    printf("  mkdir <folder_name>       - Create a new folder\n");
    printf("  cd <folder_name or ..>       - Change current directory\n");
    printf("  pwd                       - Print current directory path\n");
    printf("  touch <file_name>         - Create a new empty file\n");
    printf("  ls                        - List contents of the current folder\n");
    printf("  clear                     - Clear the screen\n");
    printf("  rm <file_name>            - Delete a file\n");
    printf("  rmdir <folder_name>       - Delete a folder (must be empty)\n");
    printf("  cat <file_name>           - Display contents of a file\n");
    printf("  echo <file_name>          - Write input into a file (overwrite)\n");
    printf("  find <file_name>          - Recursively search for a file\n");
    printf("  finddir <folder_name>     - Recursively search for a folder\n");
    printf("  scheduling                - Simulate scheduling algorithms\n");
    printf("  exit                      - Exit the OS\n");
    printf("  help                      - Display this help menu\n");
}
