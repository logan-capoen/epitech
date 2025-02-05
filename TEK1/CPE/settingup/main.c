/*
** EPITECH PROJECT, 2024
** main
** File description:
** main for setting_up
*/

#include "include/setting_up.h"
#include "include/printf.h"
#include "include/my.h"
#include <stdio.h>

static int my_len_line(char *buffer)
{
    int len = 0;
    int i = 0;

    for (; buffer[i] != '\n'; i++);
    i++;
    for (; buffer[i] != '\n'; i++)
        len++;
    return len;
}

static char **convert_to_tab(char *buffer, off_t size, int *nb_line,
    int *len_line)
{
    char **db_tab = malloc(sizeof(char *) * (my_getnbr(buffer) + 1));
    int i = 0;

    *nb_line = my_getnbr(buffer);
    (*len_line) = my_len_line(buffer);
    for (; buffer[i] != '\n'; i++);
    i++;
    for (int j = 0; j < *nb_line; j++) {
        db_tab[j] = malloc(sizeof(char) * ((*len_line) + 1));
        for (int k = 0; buffer[((*len_line) + 1) * j + k + i] != '\n'; k++)
            db_tab[j][k] = buffer[((*len_line) + 1) * j + k + i];
    }
    return db_tab;
}

char **get_tab(char *pathfile, int *nb_line, int *len_line)
{
    int fd;
    char *buffer;
    struct stat sf;

    fd = open(pathfile, O_RDONLY);
    stat(pathfile, &sf);
    buffer = malloc(sizeof(char) * sf.st_size);
    if (read(fd, buffer, sf.st_size) == 0)
        return NULL;
    if (my_getnbr(buffer) == 0)
        return NULL;
    if (handle_error_file(buffer))
        return NULL;
    if (buffer[my_len_int(my_getnbr(buffer)) + 1] == '\0')
        return NULL;
    return convert_to_tab(buffer, sf.st_size, nb_line, len_line);
}

int main(int argc, char **argv)
{
    int nb_line = 0;
    int len_line = 0;
    char **db_tab;

    if (argc == 2) {
        if (handle_error_pathfile(argv[1]) == 84)
            return 84;
        db_tab = get_tab(argv[1], &nb_line, &len_line);
        if (db_tab == NULL)
            return 84;
        setting_up(db_tab, nb_line, len_line);
        return 0;
    } else if (argc == 3) {
        db_tab = create_tab(my_getnbr(argv[1]), argv[2]);
        setting_up(db_tab, my_getnbr(argv[1]), my_getnbr(argv[1]));
        return 0;
    }
    write(2, "no file given", 13);
    return 84;
}

static int condition_pattern(int index, int len_pattern)
{
    if (index == len_pattern)
        return 0;
    return index;
}

char **create_tab(int size, char *pattern)
{
    int len_pattern = my_strlen(pattern);
    char **db_tab = malloc(sizeof(char *) * (size + 1));
    int index = 0;

    for (int i = 0; i < size; i++) {
        db_tab[i] = malloc(sizeof(char) * (size + 1));
        for (int j = 0; j < size; j++) {
            index = condition_pattern(index, len_pattern);
            db_tab[i][j] = pattern[index];
            index++;
        }
    }
    return db_tab;
}

int handle_error_pathfile(char *file_path)
{
    struct stat sf;

    if (stat(file_path, &sf) != 0) {
        write(2, "wrong pathfile", 14);
        return 84;
    }
    if (S_ISDIR(sf.st_mode) || S_ISLNK(sf.st_mode)) {
        write(2, "its not a file", 15);
        return 84;
    }
    return 0;
}

static int verif_line(int len_line, int *len_current_line)
{
    if (len_line == *len_current_line)
        return 1;
    *len_current_line = 0;
    return 0;
}

static int cond_handle_error_file(int *i, int *len_line,
    int *len_line_current, char *buff)
{
    if (buff[*i + 1] == '\n') {
        *i += 1;
        if (*len_line != *len_line_current)
            return 84;
        *len_line_current = 0;
    }
    return 0;
}

int handle_error_file(char *buff)
{
    int nb_line = my_getnbr(buff);
    int i = 1;
    int len_line = my_len_line(buff);
    int len_line_current = 1;
    int nb_current_line = 0;

    for (; buff[i - 1] != '\n'; i++);
    for (; buff[i] != '\0'; i++) {
        if (buff[i + 1] == '\n') {
            nb_current_line++;
        }
        if (cond_handle_error_file(&i, &len_line,
            &len_line_current, buff) == 84)
            return 84;
        len_line_current++;
    }
    if (nb_current_line != nb_line)
        return 84;
    return 0;
}
