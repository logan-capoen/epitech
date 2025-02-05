/*
** EPITECH PROJECT, 2025
** useful_functions.c
** File description:
** useful_functions
*/

#include <unistd.h>
#include <crypt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions_sudo.h"
#include <termios.h>

int my_len_int(int num)
{
    int len = 0;

    if (num < 0)
        num *= -1;
    for (; num > 0; len++) {
        num /= 10;
    }
    if (len == 0)
        return 1;
    return len;
}

char *int_to_str(int uid)
{
    char texte[my_len_int(uid) + 1];
    char *string_return;

    snprintf(texte, sizeof(texte), "%d", uid);
    string_return = my_strdup(texte);
    return string_return;
}

char *find_hash(void)
{
    int uid = getuid();
    char *name = get_username(int_to_str(uid), "/etc/passwd");
    char *hash = get_username(name, "/etc/shadow");

    return hash;
}

void displaying(int i)
{
    if (i == 2)
        printf("my_sudo: 3 incorrect password attempts\n");
    else
        printf("Sorry, try again.\n");
}
