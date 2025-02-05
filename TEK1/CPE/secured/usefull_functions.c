/*
** EPITECH PROJECT, 2025
** usefull_functions
** File description:
** usefull_functions
*/

#include <stdio.h>
#include "include/hashtable.h"
#include <stdlib.h>
#include <string.h>
#include "include/my.h"
#include "include/printf.h"


int ht_insert(hashtable_t *ht, char *key, char *value)
{
    int hashed_key = 0;
    node_t *new_node = malloc(sizeof(node_t));

    if (!ht || !new_node || !key || !value)
        return 84;
    hashed_key = ht->hash(key, ht->size);
    new_node->key = hashed_key;
    new_node->value = my_strdup(value);
    new_node->next = ht->lkd_lst[hashed_key % ht->size];
    ht->lkd_lst[hashed_key % ht->size] = new_node;
    return 0;
}

char *ht_search(hashtable_t *ht, char *key)
{
    int hashed_key = 0;
    node_t *current = NULL;

    if (!ht || !key)
        return NULL;
    hashed_key = ht->hash(key, ht->size);
    current = ht->lkd_lst[hashed_key % ht->size];
    while (current) {
        if (current->key == hashed_key) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

static void condition(node_t *prev,
    hashtable_t *ht, node_t *current, int index)
{
    if (prev) {
        prev->next = current->next;
    } else {
        ht->lkd_lst[index] = current->next;
    }
    free(current->value);
    free(current);
}

int ht_delete(hashtable_t *ht, char *key)
{
    int hashed_key = 0;
    int index = 0;
    node_t *current = NULL;
    node_t *prev = NULL;

    if (!ht || !key)
        return 84;
    index = ht->hash(key, ht->size) % ht->size;
    current = ht->lkd_lst[index];
    hashed_key = ht->hash(key, ht->size);
    while (current) {
        if (current->key == hashed_key) {
            condition(prev, ht, current, index);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void ht_dump(hashtable_t *ht)
{
    node_t *current = NULL;

    if (!ht)
        return;
    current = ht->lkd_lst[0];
    for (int i = 0; i < ht->size; i++) {
        my_printf("[%d]:", i);
        current = ht->lkd_lst[i];
        while (current) {
            my_printf("\n> %i - %s", current->key, current->value);
            current = current->next;
        }
        my_printf("\n");
    }
}
