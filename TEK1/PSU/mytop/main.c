/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** main for my_top
*/

#include "mytop.h"

static int parsing(char **argv, float *delay, int *end, char **user)
{
    if (strncmp(argv[0], "-d", 2) == 0) {
        *delay = strtof(argv[1], NULL);
        return 0;
    }
    if (strncmp(argv[0], "-n", 2) == 0) {
        *end = strtof(argv[1], NULL);
        return 0;
    }
    if (strncmp(argv[0], "-U", 2) == 0) {
        *user = argv[1];
        return 0;
    }
    return 84;
}

int main(int argc, char **argv)
{
    float delay = 3;
    int end = -1;
    char *user = malloc(sizeof(char) * 256);

    user = "NONE";
    if (argc % 2 != 0)
        for (int i = 0; i < (argc - 1); i += 2) {
            parsing(argv + i + 1, &delay, &end, &user);
        }
    my_top(delay, end, user);
}

struct tm *get_time(void)
{
    time_t current_time;
    struct tm *local_time;

    current_time = time(NULL);
    local_time = localtime(&current_time);
    return local_time;
}

static void key_pressed(int *line, int *ch)
{
    *ch = getch();
    if (*ch == 'q')
        exit(0);
    if (*ch == KEY_UP && *line > 0)
        *line -= 1;
    else if (*ch == KEY_DOWN)
        *line += 1;
}

int my_top(int delay, int end, char *user)
{
    int ch = 0;
    int line = 0;
    cpu_time_t prev = {0};

    read_cpu_times(&prev);
    initscr();
    noecho();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
    timeout(delay);
    for (int i = 0; i != end; i++) {
        clear();
        display_header(&prev);
        display_procs(get_procs(), line, user);
        refresh();
        key_pressed(&line, &ch);
    }
    endwin();
    return 0;
}

char **get_stat(int pid)
{
    FILE *file;
    char *path = malloc(sizeof(char) * 256);
    char *line = malloc(sizeof(char) * 4096);
    char **stat = malloc(sizeof(char *) * 53);

    if (!path || !line)
        return NULL;
    snprintf(path, 256, "/proc/%d/stat", pid);
    file = fopen(path, "r");
    free(path);
    if (!file)
        return NULL;
    fgets(line, 4096, file);
    fclose(file);
    stat = my_str_to_word_array(line);
    free(line);
    return stat;
}
