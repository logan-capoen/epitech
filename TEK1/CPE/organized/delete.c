/*
** EPITECH PROJECT, 2024
** delete.c
** File description:
** all functions to handle delete
*/

#include "libshell/shell.h"

static int free_node(linked_list_t *list)
{
    my_putstr(list->type);
    my_putstr(" n°");
    my_put_nbr(list->id);
    my_putstr(" - \"");
    my_putstr(list->name);
    my_putstr("\" deleted.\n");
    free(list);
    return 0;
}

int delete_node(void *data, char *str)
{
    int id = my_getnbr(str);
    linked_list_t *temp = *(linked_list_t **)data;
    linked_list_t *prev = *(linked_list_t **)data;

    if (temp->id == id) {
        *(linked_list_t **)data = temp->next;
        free_node(temp);
        return 0;
    }
    temp = temp->next;
    while (temp != NULL) {
        if (temp->id == id) {
            prev->next = temp->next;
            free_node(temp);
            return 0;
        }
        temp = temp->next;
        prev = prev->next;
    }
    return 84;
}

int del(void *data, char **args)
{
    if (*(linked_list_t **)data == NULL || args[0] == NULL) {
        my_printf("the list is empty\n");
        return 84;
    }
    for (int i = 0; args[i] != NULL; i++)
        if (*(linked_list_t **)data == NULL ||
            delete_node(data, args[i]) == 84) {
            my_printf("wrong id\n");
            return 84;
        }
    return 0;
}
