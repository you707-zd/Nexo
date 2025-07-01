#include "helper.h"
#include "scheduling.h"
#include "shell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    Folder *home = calloc(1, sizeof(Folder));
    home->name = "home";
    pwd = home;
    Command commands[] = {
        {"mkdir", mkdir},
        {"cd", cd},
        {"pwd", pwd_wrapper},
        {"touch", touch},
        {"ls", ls_wrapper},
        {"clear", clear_wrapper},
        {"rm", rm},
        {"rmdir", rmdir_wrapper},
        {"cat", cat},
        {"echo", echo_wrapper},
        {"find", find_wrapper},
        {"finddir", finddir_wrapper},
        {"scheduling", scheduling_wrapper},
        {"help", help}
    };

    while (1)
    {
        char *command = get_string("nexo> ");
        char *words[100];
        bool found = false;
        int words_count = separator(command, words);

        if (words_count > 0 && strcmp(words[0], "exit") == 0)
        {
            if (words_count == 1)
            {
                free(command);
                for (int i = 0; i < words_count; i++) free(words[i]);
                break;
            }

            printf("This command doesn't take any arguments!\n");
            free(command);
            for (int i = 0; i < words_count; i++) free(words[i]);
            continue;
        }
        else if (words_count == 0)
        {
            free(command);
            continue;
        }

        int command_count = sizeof(commands) / sizeof(commands[0]);
        for (int i = 0; i < command_count; i++)
        {
            if (strcmp(words[0], commands[i].cmd) == 0)
            {
                found = true;

                if (!validate_input(words[0], words_count))
                {
                    break;
                }

                if ((strcmp(commands[i].cmd, "cd") == 0) && (strcmp(words[1], "..") == 0))
                {
                    if (strcmp(pwd->name, "home") == 0)
                    {
                        printf("You are in the root, there is no parent folder\n");
                        break;
                    }
                    pwd = pwd->parent;
                }
                else
                {
                    commands[i].func(words_count > 1 ? words[1] : NULL);

                    if (strcmp(commands[i].cmd, "pwd") == 0)
                    {
                        printf("\n");
                    }
                }

                break;
            }
        }

        if (!found) printf("There's no such command!!\nUse 'help' to see available commands.\n");
        for (int i = 0; i < words_count; i++) free(words[i]);
        free(command);
    }

    free_tree(home);
    return 0;
}
