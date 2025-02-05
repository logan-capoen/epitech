/*
** EPITECH PROJECT, 2024
** add.c
** File description:
** all functions for handle add
*/

#include "libshell/shell.h"

static int is_type(char *type)
{
    if (my_strcmp(type, "ACTUATOR") == 0 || my_strcmp(type, "DEVICE")
        == 0 || my_strcmp(type, "PROCESSOR") == 0 ||
        my_strcmp(type, "SENSOR") == 0 || my_strcmp(type, "WIRE") == 0)
        return 0;
    return 84;
}

static int handle_add_error(char **args)
{
    int len = 0;

    for (int i = 0; args[i] != NULL; i++) {
        if (i % 2 == 0 && is_type(args[i]) == 84) {
            my_printf("wrong type\n");
            return 84;
        }
        len++;
    }
    if (len % 2 != 0) {
        my_printf("wrong number of argument\n");
        return 84;
    }
    return len;
}

static int set_id(void *list)
{
    int big_id = 0;
    linked_list_t *temp = *(linked_list_t **)list;

    if (temp == NULL)
        return 0;
    while (temp != NULL) {
        if (temp->id > big_id)
            big_id = temp->id;
        temp = temp->next;
    }
    return big_id + 1;
}

static int put_in_list(void *list, char *type, char *name)
{
    linked_list_t *new = malloc(sizeof(linked_list_t));

    if (!new) {
        my_printf("Memory allocation failed\n");
        return 84;
    }
    new->type = my_strdup(type);
    new->name = my_strdup(name);
    new->id = set_id(list);
    new->next = *(linked_list_t **)list;
    *(linked_list_t **)list = new;
    my_printf("%s n°%i - %c%s%c added.\n",
        new->type, new->id, '"', new->name, '"');
    return 0;
}

int add(void *data, char **args)
{
    int len = handle_add_error(args);

    if (len == 84 || args[0] == NULL)
        return 84;
    for (int i = 0; i < len; i += 2) {
        put_in_list(data, args[i], args[i + 1]);
    }
    return 0;
}
