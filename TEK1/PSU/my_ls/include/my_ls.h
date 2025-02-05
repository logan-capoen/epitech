/*
** EPITECH PROJECT, 2024
** my_ls.h
** File description:
** my_ls
*/

#ifndef MY_LS_H_
    #define MY_LS_H_
    #include <sys/types.h>
    #include <dirent.h>
    #include <stdlib.h>
    #include "struct_ls.h"
int my_ls(DIR *entry, flags_t flags, char *pathfile);
int get_flags(char *str_flags, flags_t *flags);
int sort_file(struct dirent **tab_data_file);
char *get_input(int argc, char **argv, char ***file_path,
    int *file_path_count);
int special_case(flags_t flags, int file_path_count, char **file_path);
int reverse_path_files(char ***file_path, int file_path_count);
int reverse_data_file(struct dirent ***tab_data_file);
int display(char **file_path, flags_t flags, int file_path_count);
int handling_d_flag(char **file_path, flags_t flags, int file_path_count);
int get_data_file(struct dirent ***tab_data_file, flags_t flags,
    time_t **time, DIR *entry);
int sort_pathfile(char ***pathfile);
int handle_l_flag(struct dirent **tab_data_file, char *pathfile);
int handle_error(char **file_path, flags_t flags);
int sort_file_t(struct dirent **tab_data_file, char *pathfile);
char *handle_buff(char *pathfile, char *data_file_name);
#endif
