//
// Created by golobii on 6/28/22.
//

#include "args.h"
#include <argp.h>

const char *argp_program_verison = "cshell 1.0";
static char doc[] = "cshell -- a simple and practically unusable shell.";
static char args_doc[] = "";

static struct argp_option options[] = {
        {"command", 'c', "CMD", 0,
                     "A command to execute.", 0},
        {0, 0, 0, 0, 0, 0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;

    switch (key) {
        case 'c':
            arguments->command = arg;
            break;
        case ARGP_KEY_END:
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };
