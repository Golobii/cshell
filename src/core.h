//
// Created by golobii on 6/27/22.
//

#ifndef CSHELL_CORE_H
#define CSHELL_CORE_H

#include <unistd.h>

enum EXIT_STATUS {
    S_EXIT,
    S_ERR,
    S_OK,
};

ssize_t readline(char *input);
int init_shell();
void parse(char *input, char *par[]);

enum EXIT_STATUS run(char *params[]);

#endif //CSHELL_CORE_H
