/*
** EPITECH PROJECT, 2024
** setting_up
** File description:
** main function for setting_up
*/

#include "include/setting_up.h"
#include "include/printf.h"
#include "include/my.h"

static int put_size(char current, int left, int top, int top_left)
{
    int mini = left;

    if (current != '.')
        return 0;
    if (mini > top)
        mini = top;
    if (mini > top_left)
        mini = top_left;
    return mini + 1;
}

static int max_size(bs_t *big_square, int current_size, int j, int k)
{
    if (big_square->size_max < current_size) {
        big_square->size_max = current_size;
        big_square->x = k;
        big_square->y = j;
    }
    return 0;
}

static int **create_array_size(char **tab, bs_t *big_square,
    int nb_line, int len_line)
{
    int **array_size = malloc(sizeof(int *) * (nb_line + 1));

    for (int i = 0; i < len_line; i++) {
        array_size[0] = malloc(sizeof(int) * (len_line + 1));
        array_size[0][i] = 0;
    }
    for (int j = 1; j < nb_line + 1; j++) {
        array_size[j] = malloc(sizeof(int) * (len_line + 1));
        array_size[j][0] = 0;
        for (int k = 1; k < len_line + 1; k++) {
            array_size[j][k] = put_size(tab[j - 1][k - 1], array_size[j]
                [k - 1], array_size[j - 1][k], array_size[j - 1][k - 1]);
            max_size(big_square, array_size[j][k], j, k);
        }
    }
    return array_size;
}

int setting_up(char **tab, int nb_line, int len_line)
{
    bs_t big_square = {0, 0, 0};
    int **array_size = create_array_size(tab, &big_square, nb_line, len_line);

    for (int i = 0; i < big_square.size_max; i++) {
        for (int j = 0; j < big_square.size_max; j++) {
            tab[big_square.y - i - 1][big_square.x - j - 1] = 'x';
        }
    }
    for (int k = 0; k < nb_line; k++) {
        write(1, tab[k], len_line);
        my_putstr("\n");
    }
    return 0;
}
