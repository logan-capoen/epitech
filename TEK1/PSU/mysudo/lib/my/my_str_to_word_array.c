/*
** EPITECH PROJECT, 2024
** my_str_to_word_array
** File description:
** strs biduke
*/
#include "my.h"
#include <stdlib.h>

static int my_str_isalphanum(char str)
{
    if ((str < 'a' || str > 'z') && (str < 'A' || str > 'Z')
        && (str < '0' || str > '9'))
        return 0;
    return 1;
}

static int nbr_mots(char *str2)
{
    int i = 0;
    int nbmots = 0;

    while (str2[i] != '\0'){
        if (my_str_isalphanum(str2[i]) == 0
            && my_str_isalphanum(str2[i - 1]) == 1){
            nbmots++;
        }
        i++;
    }
    return nbmots;
}

static int fautpasserlecs(char *str2, int i)
{
    if (my_str_isalphanum(str2[i]) == 0)
            i++;
    return i;
}

static char **str_to_word_part2(char *str2, char **tab, int lenmot, int nbmots)
{
    int i = 0;
    int debutmot = 0;

    while (str2[i] != '\0') {
        if (my_str_isalphanum(str2[i]) == 1
            && my_str_isalphanum(str2[i -1]) == 0)
            debutmot = i;
        for (i; (my_str_isalphanum(str2[i]) == 1); i++)
            lenmot++;
        if (my_str_isalphanum(str2[i]) == 0
            && my_str_isalphanum(str2[i - 1]) == 1){
            tab[nbmots] = malloc(lenmot * sizeof(char));
            tab[nbmots] = my_strncat(tab[nbmots], (str2 + debutmot), lenmot);
            tab[nbmots][lenmot] = '\0';
            nbmots++;
            lenmot = 0;
        }
        i = fautpasserlecs(str2, i);
    }
    return tab;
}

char **my_str_to_word_array(char *str)
{
    int len = my_strlen(str);
    char **tab;
    char *str2 = malloc((len + 2) * sizeof(char));
    int lenmot = 0;
    int nbmots = 0;

    str2 = my_strcat(str2, str);
    str2 = my_strcat(str2, " \0");
    tab = malloc((nbr_mots(str2) + 1) * sizeof(char *));
    tab = str_to_word_part2(str2, tab, lenmot, nbmots);
    tab[nbr_mots(str2)] = malloc(sizeof(char));
    tab[nbr_mots(str2)] = NULL;
    return tab;
}
