/*
** EPITECH PROJECT, 2024
** reverse.c
** File description:
** reverse functions
*/

#include "include/printf.h"
#include "include/my.h"
#include <stdio.h>
#include "include/struct_ls.h"
#include "include/my_ls.h"

int reverse_data_file(struct dirent ***tab_data_file)
{
    struct dirent *temp;
    int len = 0;

    for (int i = 0; (*tab_data_file)[i] != 0; i++)
        len++;
    for (int i = 0; i < len / 2; i++) {
        temp = (*tab_data_file)[i];
        (*tab_data_file)[i] = (*tab_data_file)[len - i - 1];
        (*tab_data_file)[len - i - 1] = temp;
    }
    return 0;
}

int reverse_path_files(char ***file_path, int file_path_count)
{
    char *temp;

    for (int i = 0; i < file_path_count / 2; i++) {
        temp = (*file_path)[i];
        (*file_path)[i] = (*file_path)[file_path_count - i - 1];
        (*file_path)[file_path_count - i - 1] = temp;
    }
    return 0;
}
