#include "helper.h"
#include "shell.h"
#include "scheduling.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *cmd;
    int runtime;
} ProcessInfo;

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
int command_count = sizeof(commands) / sizeof(commands[0]);

void FCFS(char *processes[], int processes_count, char *container[])
{
    for (int i = 0; i < processes_count; i++)
    {
        char *words[100];
        bool found = false;
        int words_count = separator(processes[i], words);

        printf("\nExecuting: %s\n", processes[i]);

        for (int j = 0; j < command_count; j++)
        {
            if (strcmp(words[0], commands[j].cmd) == 0)
            {
                found = true;

                if (!validate_input(words[0], words_count))
                {
                    break;
                }

                if ((strcmp(commands[j].cmd, "cd") == 0) && (strcmp(words[1], "..") == 0))
                {
                    if (strcmp(pwd->name, "home") == 0)
                    {
                        printf("You are in the root, there is no parent folder\n");
                        break;
                    }
                    pwd = pwd->parent;
                }
                else if (strcmp(commands[j].cmd, "echo") == 0)
                {
                    echo(words_count > 1 ? words[1] : NULL, container[i]);
                }
                else if (strcmp(commands[j].cmd, "scheduling") == 0)
                {
                    printf("You can't call scheduling inside scheduling\n");
                }
                else
                {
                    commands[j].func(words_count > 1 ? words[1] : NULL);

                    if (strcmp(commands[j].cmd, "pwd") == 0)
                    {
                        printf("\n");
                    }
                }

                break;
            }
        }

        if (!found) printf("There's no such command!!\nUse 'help' to see available commands.\n");


        for (int i = 0; i < words_count; i++) free(words[i]);
    }
}

int get_burst_time(char *cmd)
{
    if (strcmp(cmd, "clear") == 0)
    {
        return 1;
    }
    else if ((strcmp(cmd, "pwd") == 0) || (strcmp(cmd, "echo") == 0) || (strcmp(cmd, "help") == 0))
    {
        return 2;
    }
    else if (strcmp(cmd, "cd") == 0)
    {
        return 3;
    }
    else if (strcmp(cmd, "touch") == 0)
    {
        return 4;
    }
    else if ((strcmp(cmd, "mkdir") == 0) || (strcmp(cmd, "rm") == 0))
    {
        return 5;
    }
    else if ((strcmp(cmd, "ls") == 0) || (strcmp(cmd, "cat") == 0))
    {
        return 6;
    }
    else if (strcmp(cmd, "rmdir") == 0)
    {
        return 7;
    }
    else if ((strcmp(cmd, "find") == 0) || (strcmp(cmd, "finddir") == 0))
    {
        return 8;
    }

    return -1;
}

void bubble_sort(ProcessInfo commands[], int processes_count)
{
    for (int i = 0; i < processes_count - 1; i++)
    {
        for (int j = 0; j < processes_count - i - 1; j++)
        {
            if (commands[j].runtime > commands[j + 1].runtime)
            {
                ProcessInfo temp = commands[j];
                commands[j] = commands[j + 1];
                commands[j + 1] = temp;
            }
        }
    }
}

void SJF(char *processes[], int processes_count, char *container[])
{
    ProcessInfo commands[processes_count];
    for (int i = 0; i < processes_count; i++)
    {
        char *words[100];
        int words_count = separator(processes[i], words);

         commands[i].runtime = get_burst_time(words[0]);
         commands[i].cmd = strdup(processes[i]);

        for (int j = 0; j < words_count; j++) free(words[j]);
    }

    bubble_sort(commands, processes_count);
    char *sorted_processes[processes_count];
    for (int i = 0; i < processes_count; i++)
    {
        sorted_processes[i] = strdup(commands[i].cmd);
    }

    FCFS(sorted_processes, processes_count, container);

    for (int i = 0; i < processes_count; i++)
    {
        free(sorted_processes[i]);
        free(commands[i].cmd);
    }
}

void scheduling(void)
{
    int processes_count = get_int("How many commands you want to execute? ");
    char *processes[processes_count];
    char *container[processes_count];

    printf("\n⚠️  Note: 'echo' collects input before any scheduled commands are executed.\n");
    printf("   If the target file is created later in the queue, 'echo' may fail to write.\n");
    printf("   Note: exit is not allowed inside scheduling mode.\n\n");

    for (int i = 0; i < processes_count; i++)
    {
        processes[i] = get_string("nexo> ");
        char *words[100];
        int words_count = separator(processes[i], words);

        container[i] = (strcmp(words[0], "echo") == 0) ? get_string("Enter Input: ") : NULL;

        for (int j = 0; j < words_count; j++) free(words[j]);
    }

    printf("\nChoose the algorithm: \n\n");
    printf("[1] FCFS (First-Come First-Served)\n[2] SJF (Shortest Job First)\n");

    char *algorithm = get_string("\nEnter: ");
    if ((strcasecmp(algorithm, "FCFS") == 0) ||  strcmp(algorithm, "1") == 0)
    {
        FCFS(processes, processes_count, container);
    }
    else if ((strcasecmp(algorithm, "SJF") == 0) ||  strcmp(algorithm, "2") == 0)
    {
        SJF(processes, processes_count, container);
    }
    else
    {
        printf("Invalid algorithm choice!!\n");
    }

    for (int i = 0; i < processes_count; i++)
    {
        free(processes[i]);
        if (container[i]) free(container[i]);
    }

    free(algorithm);
}

void scheduling_wrapper(char *arg)
{
    (void)arg;
    scheduling();
}
