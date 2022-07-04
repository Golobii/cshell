//
// Created by golobii on 6/28/22.
//

#ifndef CSHELL_ARGS_H
#define CSHELL_ARGS_H

#include <argp.h>

struct arguments {
    char *command;
};

extern struct argp argp;

#endif //CSHELL_ARGS_H
