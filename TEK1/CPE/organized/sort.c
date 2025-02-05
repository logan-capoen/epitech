/*
** EPITECH PROJECT, 2024
** sort.c
** File description:
** all functions to handle sort
*/

#include <stdio.h>
#include "shell.h"

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *previous = NULL;
    linked_list_t *next = NULL;
    linked_list_t *current = *begin;

    while (current != NULL) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *begin = previous;
}

static char *get_value(char **args, linked_list_t *data)
{
    if (my_strcmp(args[0], "NAME") == 0)
        return data->name;
    if (my_strcmp(args[0], "TYPE") == 0)
        return data->type;
    if (my_strcmp(args[0], "ID") == 0)
        return 0;
    return "error";
}

static int verify_values(char **args,
    linked_list_t *data1, linked_list_t *data2)
{
    if (my_strcmp(args[0], "ID") == 0)
        return data1->id - data2->id;
    return my_strcmp(get_value(args, data1), get_value(args, data2));
}

static void sorted_insert(linked_list_t **sorted,
    linked_list_t *new_node, char **args)
{
    linked_list_t *current = malloc(sizeof(linked_list_t));

    if (*sorted == NULL || verify_values(args, *sorted, new_node) > 0) {
        new_node->next = *sorted;
        *sorted = new_node;
    } else {
        current = *sorted;
        while (current->next != NULL &&
            verify_values(args, current->next, new_node) <= 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

static int sort_list(linked_list_t **head, char **args, int reverse)
{
    linked_list_t *sorted = NULL;
    linked_list_t *current = *head;
    linked_list_t *next = malloc(sizeof(linked_list_t));

    while (current != NULL) {
        next = current->next;
        current->next = NULL;
        sorted_insert(&sorted, current, args);
        current = next;
    }
    *head = sorted;
    if (reverse)
        my_rev_list(head);
    return 0;
}

static char **get_args(char **args)
{
    char *temp = malloc(sizeof(char) * 256);
    int len = my_len_dstr(args);

    if (!temp)
        return args;
    for (int i = 0; i < len / 2; i++) {
        temp = args[i];
        args[i] = args[len - i - 1];
        args[len - i - 1] = temp;
    }
    return args;
}

int sort(void *data, char **args)
{
    int reverse = 0;

    args = get_args(args);
    if (*(linked_list_t **)data == NULL)
        return 84;
    for (int i = 0; args[i] != NULL; i++) {
        if (my_strcmp(args[i], "ID") != 0 && (my_strcmp(get_value(args + i,
            *(linked_list_t **)data), "error") == 0 &&
            my_strcmp(args[i], "-r") != 0)) {
            return 84;
        }
        if (my_strcmp(args[i], "-r") == 0) {
            reverse = 1;
        } else {
            sort_list(&(*(linked_list_t **)data), args + i, reverse);
            reverse = 0;
        }
    }
    return 0;
}
