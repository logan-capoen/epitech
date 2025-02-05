/*
** EPITECH PROJECT, 2023
** B-CPE-110 : Setting Up Shell
** File description:
** shell.h
*/

#ifndef SHELL_H
    #define SHELL_H
    #include "unistd.h"
    #include "printf.h"
    #include "my.h"
    #include <stdlib.h>

typedef struct linked_list {
    int id;
    char *name;
    char *type;
    struct linked_list *next;
}linked_list_t;

int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int disp(void *data, char **args);
int delete_node(void *data, char *str);
int len_linked_list(linked_list_t *data);
char *its(int num);
int my_len_dstr(char **str);
void my_rev_list(linked_list_t **begin);

// Already implemented
int workshop_shell(void *data);

#endif
