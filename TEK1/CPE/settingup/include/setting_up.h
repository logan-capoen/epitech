/*
** EPITECH PROJECT, 2024
** setting_up.h
** File description:
** header for setting_up
*/

#ifndef SETTING_UP
    #define SETTING_UP
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>
typedef struct bs {
    int size_max;
    int x;
    int y;
} bs_t;
char **get_tab(char *pathfile, int *nb_line, int *len_line);
int setting_up(char **tab, int nb_line, int len_line);
char **create_tab(int size, char *pattern);
int handle_error_pathfile(char *file_path);
int handle_error_file(char *buff);
#endif
