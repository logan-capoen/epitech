/*
** EPITECH PROJECT, 2024
** tools_functions.c
** File description:
** all functions usefull for the project
*/


#include <stdio.h>
#include "shell.h"

int len_linked_list(linked_list_t *data)
{
    int len = 0;

    while (data != NULL) {
        len++;
        data = data->next;
    }
    return len;
}

int my_len_dstr(char **str)
{
    int len = 0;

    for (; str[len] != NULL; len++);
    return len;
}

char *its(int num)
{
    char *buff = malloc(sizeof(char) * 256);

    for (int i = 0; num > 0; i++) {
        buff[i] = num % 10 + '0';
        num /= 10;
    }
    return buff;
}
