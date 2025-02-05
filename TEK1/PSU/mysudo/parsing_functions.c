/*
** EPITECH PROJECT, 2025
** parsing_functions
** File description:
** c files for parsing functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "functions_sudo.h"

static int parse_argument(char **argv, int index, int *env, int argc)
{
    if (strcmp(argv[index], "-u") == 0)
        if (index + 1 < argc)
            return handle_flag_u(argv[index + 1]);
    if (strcmp(argv[index], "-g") == 0)
        if (index + 1 < argc)
            return handle_flag_g(argv[index + 1]);
    if (strcmp(argv[index], "-E") == 0) {
        *env = 1;
        return 1;
    }
    if (strcmp(argv[index], "-s") == 0)
        return handle_flag_s();
    if (strcmp(argv[index], "-h") == 0) {
        display_flag_h();
        exit(0);
    }
    write(2, "wrong flags\n", 12);
    exit(84);
}

int parse_options(int argc, char **argv, int *env)
{
    int len = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            len += parse_argument(argv, i, env, argc);
        }
    }
    return len;
}
