#include <stdio.h>
#include <string.h>
#include <argp.h>
#include <stdlib.h>
#include <form.h>

#include "core.h"
#include "definitions.h"
#include "internal_cmds.h"
#include "args.h"

int start_interactive();


char *trimwhitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)  // All spaces?
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    // Write new null terminator character
    end[1] = '\0';

    return str;
}

bool is_interactive() {
    char *term = getenv("TERM");

    if (term == NULL) {
        return false;
    }

    return true;
}


int main(int argc, char **argv) {
    if (init_shell() != 0) {
        puts("Failed to init shell.");
        return -1;
    }

    struct arguments arguments;

    arguments.command = "";

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    char input[MAX_CHARS];
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

    /*
    if (is_interactive()) {
        return start_interactive();
    }*/

    char running = 1;
    while (running) {
        ssize_t len = readline(input);
        if (len == -1) return -1;
        else if (len == 1) continue;

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

    endwin();
    return 0;
}

int start_interactive() {
    return -1;
}