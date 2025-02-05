/*
** EPITECH PROJECT, 2024
** handling.c
** File description:
** handling for input, flags, etc
*/

#include "include/printf.h"
#include "include/my.h"
#include <stdio.h>
#include "include/struct_ls.h"
#include "include/my_ls.h"
#include <sys/stat.h>
#include <unistd.h>

static int condition_sort_file(struct dirent **tab_data_file,
    struct dirent **min, int j, int i)
{
    if (my_strcmp(my_strlowcase(my_strdup(tab_data_file[j]->d_name)),
        my_strlowcase(my_strdup((*min)->d_name))) == -1) {
                *min = tab_data_file[j];
                tab_data_file[j] = tab_data_file[i];
                tab_data_file[i] = *min;
            }
}

int sort_file(struct dirent **tab_data_file)
{
    struct dirent *min;

    for (int i = 0; tab_data_file[i] != NULL; i++) {
        min = tab_data_file[i];
        for (int j = i; tab_data_file[j] != NULL; j++) {
            condition_sort_file(tab_data_file, &min, j, i);
        }
    }
    return 0;
}

static int condition_sort_pathfile(char ***pathfile, char **min, int j, int i)
{
    if (my_strcmp(my_strlowcase(my_strdup((*pathfile)[j])),
        my_strlowcase(my_strdup((*min)))) == -1) {
                *min = (*pathfile)[j];
                (*pathfile)[j] = (*pathfile)[i];
                (*pathfile)[i] = *min;
            }
            return 0;
}

int sort_pathfile(char ***pathfile)
{
    char *min;

    for (int i = 0; (*pathfile)[i] != NULL; i++) {
        min = (*pathfile)[i];
        for (int j = i; (*pathfile)[j] != NULL; j++)
            condition_sort_pathfile(pathfile, &min, j, i);
    }
    return 0;
}

static int in_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
        return 1;
    }
    return 0;
}

int get_flags(char *str_flags, flags_t *flags)
{
    for (int i = 0; str_flags[i] != '\0'; i++) {
        if ('a' == str_flags[i])
            flags->a = 1;
        if ('l' == str_flags[i])
            flags->l = 1;
        if ('R' == str_flags[i])
            flags->R = 1;
        if ('d' == str_flags[i])
            flags->d = 1;
        if ('r' == str_flags[i])
            flags->r = 1;
        if ('t' == str_flags[i])
            flags->t = 1;
        if (in_str(str_flags[i], "alRdrt") == 0)
            return 84;
    }
    return 0;
}

char *get_input(int argc, char **argv, char ***file_path, int *file_path_count)
{
    char *flags;
    int len = 0;

    for (int i = 1; i < argc; i++)
        len += my_strlen(argv[i]);
    flags = malloc(sizeof(char) * (len + 1));
    flags[0] = '\0';
    for (int j = 1; argv[j] != 0; j++) {
        if (argv[j][0] == '-')
            my_strcat(flags, argv[j] + 1);
    }
    for (int k = 1; argv[k] != 0; k++) {
        if (argv[k][0] != '-') {
            (*file_path)[(*file_path_count)] = argv[k];
            (*file_path_count) += 1;
        }
    }
    return flags;
}

int special_case(flags_t flags, int file_path_count, char **file_path)
{
    if (file_path_count == 0) {
        my_ls(opendir("."), flags, ".");
        return 1;
    }
    if (file_path_count == 1 || flags.l) {
        my_ls(opendir(file_path[0]), flags, file_path[0]);
        return 1;
    }
    return 0;
}
