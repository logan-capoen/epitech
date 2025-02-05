/*
** EPITECH PROJECT, 2024
** get_procs.c
** File description:
** get all informations of procs
*/

#include "include/mytop.h"

static void add_pr(char *pr, proc_t **new)
{
    if (atoi(pr) == -100)
        (*new)->pr = "rt";
    else
        (*new)->pr = pr;
}

static proc_t *add_info_proc(char *pid, int is_first, proc_t **procs)
{
    char **stat = get_stat(my_getnbr(pid));
    proc_t *new = malloc(sizeof(proc_t));

    new->pid = pid;
    new->username = get_username(my_getnbr(pid));
    add_pr(stat[17], &new);
    new->ni = stat[18];
    new->virt = stat[22];
    new->state = stat[2][0];
    new->time = atoi(stat[13]) + atoi(stat[14]);
    if (is_first)
        new->next = *procs;
    else
        new->next = NULL;
    for (int i = 0; stat[i] != NULL; i++)
        if (i != 17 && i != 18 && i != 22 &&
        i != 2 && i != 13 && i != 14)
            free(stat[i]);
    free(stat);
    return new;
}

static int put_proc(proc_t **procs, char *pid)
{
    char **stat = get_stat(my_getnbr(pid));
    proc_t *temp = *procs;

    if (!stat)
        return 0;
    if (*procs == NULL) {
        *procs = add_info_proc(pid, 1, procs);
        return 0;
    }
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = add_info_proc(pid, 0, procs);
    for (int i = 0; stat[i] != NULL; i++)
        free(stat[i]);
    free(stat);
    return 0;
}

proc_t *get_procs(void)
{
    proc_t *procs = NULL;
    DIR *entry = opendir("/proc");
    struct dirent *data = readdir(entry);

    while (data != NULL) {
        if (my_getnbr(data->d_name) != 0)
            put_proc(&procs, data->d_name);
        data = readdir(entry);
    }
    closedir(entry);
    return procs;
}

char *get_username(int pid)
{
    FILE *file;
    int uid = -1;
    struct passwd *pwd;
    char *line = malloc(256);
    char *path = malloc(256);

    sprintf(path, "/proc/%d/status", pid);
    file = fopen(path, "r");
    while (fgets(line, 256, file)) {
        if (strncmp(line, "Uid:", 4) == 0 &&
            sscanf(line, "Uid: %d", &uid) == 1)
            break;
    }
    fclose(file);
    free(path);
    free(line);
    pwd = getpwuid(uid);
    return strdup(pwd->pw_name);
}

unsigned long get_res(int pid)
{
    char path[256];
    char line[256];
    FILE *file;
    unsigned long res_mem = 0;

    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    file = fopen(path, "r");
    if (!file)
        return 0;
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %lu kB", &res_mem);
            fclose(file);
            return res_mem;
        }
    }
    fclose(file);
    return 0;
}

char *get_command_name(int pid)
{
    char path[64];
    char *command = malloc(sizeof(char) * 256);
    FILE *file;

    if (!command)
        return NULL;
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    file = fopen(path, "r");
    if (!file) {
        free(command);
        return NULL;
    }
    if (!fgets(command, 256, file)) {
        free(command);
        fclose(file);
        return NULL;
    }
    fclose(file);
    command[strcspn(command, "\n")] = '\0';
    return command;
}
