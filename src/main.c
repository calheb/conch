#define _POSIX_C_SOURCE 200112L
#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT 810
#define MAX_TOKENS 10
#define MAX_PIDS 5

/* record of child PIDs, capped at MAX_PIDS*/
static pid_t pids[MAX_PIDS];
static int pid_count = 0;

/*
 * builtin_exit - free history and exit
 */
static void builtin_exit(History *h)
{
    history_free(h);
    printf("exit\n");
    _exit(0);
}

/*
 * builtin_showpid - print all recorded child PIDs, one per line
 */
static void builtin_showpid(void)
{
    int i;
    for (i = 0; i < pid_count; i++) {
        printf("%d\n", pids[i]);
    }
}

/*
 * builtin_cd - change the working directory to path and update PWD
 */
static void builtin_cd(char *path, char *cwd)
{
    if (chdir(path) != 0) {
        printf("Error: cannot change directory.\n");
    }
    else {
        (void)getcwd(cwd, MAX_INPUT + 1);
        setenv("PWD", cwd, 1);
    }
}

/*
 * builtin_history - print the command history
 */
static void builtin_history(const History *h)
{
    history_print(h);
}

/*
 * record_pid - append pid to pids[], if it's full remove the oldest and shift
 */
static void record_pid(pid_t pid)
{
    int i;
    if (pid_count == MAX_PIDS) {
        for (i = 0; i < MAX_PIDS - 1; i++) {
            pids[i] = pids[i + 1];
            pids[MAX_PIDS - 1] = pid;
        }
    }
    else {
        pids[pid_count++] = pid;
    }
}

/*
 * execute_command - fork and exec an external command, then record its PID
 */
static void execute_command(char **tokens)
{
    pid_t pid;
    if ((pid = fork()) == 0) {
        execvp(tokens[0], tokens);
        printf("Error: command could not be executed\n");
        _exit(1);
    }
    else {
        waitpid(pid, NULL, 0);
        record_pid(pid);
    }
}

int main(void)
{
    char input[MAX_INPUT + 1];
    char *tokens[MAX_TOKENS];
    int token_count;
    char cwd[MAX_INPUT + 1];
    History history;

    history_init(&history, 16);

    while (1) {
        memset(input, 0, sizeof(input));
        (void)getcwd(cwd, sizeof(cwd));

        /* green text for the prompt, then reset */
        printf("\n\x1b[32m%s$ ", cwd);
        printf("\x1b[0m");

        if (fgets(input, MAX_INPUT, stdin) == NULL)
            continue;

        input[strcspn(input, "\n")] = '\0';

        /* skip blank lines */
        if (input[0] == '\0')
            continue;

        history_add(&history, input);

        /* tokenize input */
        token_count = 0;
        tokens[token_count] = strtok(input, " ");

        while (tokens[token_count] != NULL && token_count < MAX_TOKENS - 1) {
            tokens[++token_count] = strtok(NULL, " ");
        }

        tokens[token_count] = NULL; /* null-terminate for execvp */

        /* builtins */
        if (strcmp(tokens[0], "exit") == 0) {
            builtin_exit(&history);
            continue;
        }
        if (strcmp(tokens[0], "showpid") == 0) {
            builtin_showpid();
            continue;
        }
        if (strcmp(tokens[0], "cd") == 0) {
            builtin_cd(tokens[1], cwd);
            continue;
        }
        if (strcmp(tokens[0], "history") == 0) {
            builtin_history(&history);
            continue;
        }

        /* external command */
        execute_command(tokens);
    }

    return 0;
}
