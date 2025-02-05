/*
** EPITECH PROJECT, 2024
** my_getnbr
** File description:
** my_getnbr
*/
#include "my.h"
static int suite2(long reponse, int nega, char const *str, int index)
{
    if (str[index] < 48 || str[index] > 57){
        if ((nega % 2) != 0){
            return reponse;
        } else
            return 0;
    }
    return 0;
}

static int suite1(int index, int nega, char const *str)
{
    long reponse = 0;
    int reponsefin = 0;
    int faux = 2;

    while ((str[index] > 47 && str[index] < 58)){
        reponse *= 10;
        reponse += (str[index]-48);
        index++;
        if (reponse == 2147483648)
            faux = suite2(reponse, nega, str, index);
        if (reponse > 2147483647 && reponse != 2147483648)
            return 0;
    }
    if (faux == 0)
        return 0;
    if ((nega % 2) != 0)
        reponse *= -1;
    reponsefin = reponse;
    return reponsefin;
}

int my_getnbr(char const *str)
{
    int index = 0;
    int nega = 0;

    while (str[index] < 48 || str[index] > 57){
        if ((str[index] < 48 || str[index] > 57)
            && str[index] != '-' && str[index] != '+')
            return 0;
        if (str[index] == '-')
            nega--;
        index++;
    }
    if (suite1(index, nega, str) == 0){
        return 0;
    } else {
        return suite1(index, nega, str);
    }
}
