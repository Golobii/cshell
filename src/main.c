#include <stdio.h>
#include <string.h>
#include <argp.h>
#include <readline/history.h>
#include <stdlib.h>

#include "core.h"
#include "definitions.h"
#include "args.h"

int main(int argc, char **argv) {
    if (init_shell() != 0) {
        puts("Failed to init shell.");
        return -1;
    }

    struct arguments arguments;

    arguments.command = "";

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    char *params[MAX_WORDS] = {0};

    if (strcmp(arguments.command, "") != 0) {
        parse(arguments.command, params);
        add_history(arguments.command);
        switch (run(params)) {
            case S_EXIT:
                goto end;
            case S_ERR:
                puts("There was an error.");
                break;
            case S_OK:
                break;
        }
        end:
        exit_shell();
        return 0;
    }

    char running = 1;
    while (running) {
        char *input = rl_gets();

        if (strcmp(input, "") == 0) continue;

        parse(input, params);

        switch (run(params)) {
            case S_EXIT:
                exit_shell();
                return 0;
            case S_ERR:
                puts("There was an error.");
                break;
            case S_OK:
                break;
        }

    }

    return 0;
}