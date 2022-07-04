//
// Created by golobii on 6/27/22.
//

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "internal_cmds.h"

void execCd(char *dest) {
    if (dest == NULL) {
        chdir(getenv("HOME"));
        return;
    }

    chdir(dest);
}

void execHelp() {
    printf("Imagine here being a good help section\n\n");
}

int execInternalCmd(char *command, char *params[]) {
    if (strcmp(command, "cd") == 0) {
        execCd(params[1]);
        return 0;
    } else if (strcmp(command, "help") == 0) {
        execHelp();
        return 0;
    }
    return 1;
}
