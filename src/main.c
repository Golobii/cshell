#include <stdio.h>
#include <string.h>
#include <argp.h>

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
        switch (run(params)) {
            case S_EXIT:
                puts("exit");
                return 0;
            case S_ERR:
                puts("There was an error.");
                break;
            case S_OK:
                break;
        }
        return 0;
    }

    char running = 1;
    while (running) {
        char *input = rl_gets();

        parse(input, params);

        switch (run(params)) {
            case S_EXIT:
                puts("exit");
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