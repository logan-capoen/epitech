/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main
*/

#include "include/my.h"
#include <stdio.h>
#include "include/struct_ls.h"
#include "include/printf.h"
#include "include/my_ls.h"
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int file_path_count = 0;
    char **file_path = malloc(sizeof(char *) * (argc));
    char *str_flags = get_input(argc, argv, &file_path, &file_path_count);
    flags_t flags = {0, 0, 0, 0, 0, 0};

    if (handle_error(file_path, flags) == 84)
        return 84;
    sort_pathfile(&file_path);
    if (get_flags(str_flags, &flags) == 84)
        return 84;
    if (flags.r)
        reverse_path_files(&file_path, file_path_count);
    if (handling_d_flag(file_path, flags, file_path_count))
        return 0;
    if (special_case(flags, file_path_count, file_path))
        return 0;
    return display(file_path, flags, file_path_count);
}

int display(char **file_path, flags_t flags, int file_path_count)
{
    for (int i = 0; file_path[i] != 0; i++) {
        my_printf("%s:\n", file_path[i]);
        my_ls(opendir(file_path[i]), flags, file_path[i]);
        if (i != file_path_count - 1)
            my_printf("\n");
    }
    return 0;
}

int handling_d_flag(char **file_path, flags_t flags, int file_path_count)
{
    if (flags.d) {
        if (file_path_count == 0) {
            my_printf(".\n");
            return 1;
        }
        for (int i = 0; i < file_path_count; i++)
            my_printf("%s  ", file_path[i]);
        my_printf("\n");
        return 1;
    }
    return 0;
}

int handle_error(char **file_path, flags_t flags)
{
    struct stat sf;
    DIR *dir;

    for (int i = 0; file_path[i] != NULL; i++) {
        dir = opendir(file_path[i]);
        if (!dir || stat(file_path[i], &sf) != 0)
            return 84;
        if (!S_ISDIR(sf.st_mode)) {
            my_printf("%s", file_path[i]);
            exit(84);
            return 84;
        }
    }
    return 0;
}
