/*
** EPITECH PROJECT, 2024
** my_ls.c
** File description:
** main file for my_ls
*/

#include "include/printf.h"
#include "include/my.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/struct_ls.h"
#include <sys/stat.h>
#include <time.h>
#include "include/my_ls.h"

int my_ls(DIR *entry, flags_t flags, char *pathfile)
{
    struct dirent **tab_data_file = malloc(sizeof(struct dirent*) * 1024);
    time_t *time = malloc(sizeof(int) * 1024);
    char *file;
    int i = 0;

    get_data_file(&tab_data_file, flags, &time, entry);
    sort_file(tab_data_file);
    if (flags.t)
        sort_file_t(tab_data_file, pathfile);
    if (flags.r)
        reverse_data_file(&tab_data_file);
    if (flags.l)
        return handle_l_flag(tab_data_file, pathfile);
    for (int j = 0; tab_data_file[j] != NULL; j++)
        my_printf("%s\n", tab_data_file[j]->d_name);
    return 0;
}

int get_data_file(struct dirent ***tab_data_file, flags_t flags,
    time_t **time, DIR *entry)
{
    struct dirent *data_file = readdir(entry);
    int i = 0;
    struct stat sf;

    while (data_file != NULL) {
        if (data_file->d_name[0] != '.' || flags.a == 1) {
            (*tab_data_file)[i] = data_file;
            stat(data_file->d_name, &sf);
            (*time)[i] = sf.st_mtime;
            i++;
        }
        data_file = readdir(entry);
    }
    return 0;
}

static int cond_sort_file_t(struct dirent **tab_data_file,
    int i, char *pathfile)
{
    struct stat sf;
    struct dirent *min;
    int min_int;

    stat(handle_buff(pathfile, tab_data_file[i]->d_name), &sf);
        min = tab_data_file[i];
        min_int = sf.st_mtime;
        for (int j = i; tab_data_file[j] != NULL; j++) {
            stat(handle_buff(pathfile, tab_data_file[j]->d_name), &sf);
            if (min_int < sf.st_mtime) {
                min = tab_data_file[j];
                tab_data_file[j] = tab_data_file[i];
                tab_data_file[i] = min;
                min_int = sf.st_mtime;
            }
        }
}

int sort_file_t(struct dirent **tab_data_file, char *pathfile)
{
    for (int i = 0; tab_data_file[i] != NULL; i++) {
        cond_sort_file_t(tab_data_file, i, pathfile);
    }
    return 0;
}
