/*
** EPITECH PROJECT, 2024
** display.c
** File description:
** all functions to handle disp
*/

#include "libshell/shell.h"

int disp(void *data, char **args)
{
    linked_list_t *temp = *(linked_list_t **)data;

    if (args[0] != NULL)
        return 84;
    while (temp != NULL) {
        my_printf("%s n°%i - %c%s%c\n", temp->type,
        temp->id, '"', temp->name, '"');
        temp = temp->next;
    }
    return 0;
}
