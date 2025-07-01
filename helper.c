#include "helper.h"
#include "shell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Folder *pwd;

char *get_string(char *prompt)
{
    //My own version of get_string
    printf("%s", prompt);

    size_t buffer_size = 16;
    size_t length = 0;

    char *buffer = malloc(buffer_size);
    if (buffer == NULL)
    {
        printf("No enough memory!! \n");
        return NULL;
    }

    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        buffer[length++] = (char) c;

        if (length == buffer_size)
        {
            buffer_size *= 2;

            char *temp = realloc(buffer, buffer_size);
            if (temp == NULL)
            {
                free(buffer);
                printf("No enough memory!! \n");
                return NULL;
            }

            buffer = temp;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int separator(char *input, char *words[100])
{
    int number = 0;
    int i = 0;
    int start = 0;
    int length = strlen(input);

    while (i <= length)
    {
        if (input[i] == ' ' || input[i] == '\n' || input[i] == '\0')
        {
            int word_length = i - start;
            if (word_length > 0)
            {
                char *word = malloc(word_length + 1);
                strncpy(word, &input[start], word_length);
                word[word_length] = '\0';
                words[number++] = word;
            }
            start = i + 1;
        }
        i++;
    }

    return number;
}

int get_int(char *prompt)
{
    //My own version of get_int
    char buffer[100];
    char *endptr;
    long value;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            continue;
        }

        value = strtol(buffer, &endptr, 10);

        while (*endptr == ' ' || *endptr == '\t')
            endptr++;

        if (*endptr == '\n' || *endptr == '\0')
        {
            return (int) value;
        }
    }
}

void free_tree(Folder *home)
{
    for (int i = 0; i < home->file_children_count; i++)
    {
        remove(home->file_children[i]->filename);
        free(home->file_children[i]->filename);
        free(home->file_children[i]);
    }

    for (int i = 0; i < home->children_count; i++)
    {
        if (home->children[i] != NULL)
        {
            free_tree(home->children[i]);
        }
    }

    if (home->name_allocated)
    {
        free(home->name);
    }

    free(home);
}

bool validate_input(char *cmd, int words_count)
{
    const char *no_args[] = {"pwd", "clear", "ls", "scheduling", "help"};
    int no_args_count = sizeof(no_args) / sizeof(no_args[0]);

    for (int i = 0; i < no_args_count; i++)
    {
        if (strcmp(cmd, no_args[i]) == 0)
        {
            if (words_count > 1)
            {
                printf("This command doesn't take any arguments!\n");
                return false;
            }
            return true;
        }
    }

    if (words_count < 2)
    {
        printf("Too few arguments!\n");
        return false;
    }
    if (words_count > 2)
    {
        printf("Too many arguments!\n");
        return false;
    }

    return true;
}
