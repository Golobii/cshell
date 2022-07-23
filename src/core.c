//
// Created by golobii on 6/27/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>

#include "core.h"
#include "definitions.h"
#include "internal_cmds.h"

static char *hostname;

void sig_handler(int sigcode) {
}

ssize_t readline(char *input) {
    char cwd[MAX_CHARS];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("Couldn't get the current dir.");
        return -1;
    }

    printf("\n%s@%s:%s$ ", getenv("USER"), hostname, cwd);

    char *line = NULL;
    size_t len = 0;
    ssize_t lineSize = 0;
    lineSize = getline(&line, &len, stdin);

    if (lineSize > MAX_CHARS) return 0;

    line[strlen(line) - 1] = 0;
    strcpy(input, line);
    free(line);

    return lineSize;
}

int init_shell() {
    hostname = malloc(sizeof(char) * 20);
    gethostname(hostname, sizeof(hostname));

    if (hostname == NULL) {
        printf("Can't get hostname.");
        return -1;
    }

    signal(SIGINT, sig_handler);

    return 0;
}

void parse(char *input, char *par[]) {
    char *arr[MAX_WORDS] = {0};
    char *pch;
    unsigned int i = 0;

    pch = strtok(input, " ");
    arr[i++] = pch;
    while (pch != NULL) {
        pch = strtok(NULL, " ");
        arr[i++] = pch;
    }

    free(pch);
    if (!arr[0]) return;

    for (unsigned int j = 0; j < i; j++) {
        par[j] = arr[j];
    }
}

enum EXIT_STATUS run(char *params[]) {
    bool first = true;
    u_int pipenum = 0, pipeindex = 0;
    bool needs_piping = false;

    for (u_int i = 0; params[i] != NULL; i++) {
        if (strcmp(params[i], "|") == 0) pipenum++;
    }
    int fd[pipenum][2];

    for (u_int i = 0; i < pipenum; i++) {
        if (pipe(fd[i]) < 0) {
            puts("Failed to init pipe!");
            return -1;
        }
    }

    for (unsigned int i = 0; params[i] != NULL; i++) {
        char *execParams[MAX_WORDS] = {0};
        u_int index = 0;
        if (!first) i++;
        else first = false;

        bool piping = false;

        for (; params[i] != NULL; i++) {
            if (strcmp(params[i], "&&") == 0) break;
            if (strcmp(params[i], "|") == 0) {
                piping = true;
                break;
            }
            execParams[index++] = params[i];
        }
        i--;

        if (strcmp(execParams[0], "exit") == 0) {
            return S_EXIT;
        }

        // execution
        pid_t id = fork();
        int status;


        if (id == 0) {
            if (piping) {
                dup2(fd[pipeindex][1], STDOUT_FILENO);
            }

            if (needs_piping) {
                dup2(fd[pipeindex - 1][0], STDIN_FILENO);
            }

            if (execInternalCmd(execParams[0], execParams) == 0)
                exit(0);

            int code = execvp(execParams[0], execParams);

            if (code == -1) {
                printf("Command not found\n");
            }

            // exit from child process
            exit(code);
        }


        if (piping) {
            close(fd[pipeindex][1]);
            pipeindex++;
            needs_piping = true;
        } else {
            needs_piping = false;
        }
        waitpid(id, &status, 0);

    }

    return S_OK;
}