/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** main
*/

#include <stdio.h>
#include "include/hashtable.h"
#include <stdlib.h>
#include <string.h>

int hash(char *value, int len)
{
    unsigned int hash = 2166136261u;
    unsigned int prime = 16777619u;

    if (!value)
        return 84;
    for (int i = 0; i < len; i++) {
        hash ^= (unsigned int)value[i];
        hash *= prime;
    }
    return (int)(hash & 0x7FFFFFFF);
}

hashtable_t *new_hashtable(int (*hash)(char *, int), int len)
{
    hashtable_t *ht = malloc(sizeof(hashtable_t));

    if (!ht || len <= 0 || len >= 5000)
        return NULL;
    ht->size = len;
    ht->hash = hash;
    ht->lkd_lst = malloc(sizeof(node_t *) * len);
    if (!(ht->lkd_lst)) {
        free(ht);
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        ht->lkd_lst[i] = NULL;
    }
    return ht;
}

void delete_hashtable(hashtable_t *ht)
{
    node_t *current;
    node_t *temp;

    if (!ht)
        return;
    for (int i = 0; i < ht->size; i++) {
        current = ht->lkd_lst[i];
        while (current) {
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(ht->lkd_lst);
    free(ht);
}
