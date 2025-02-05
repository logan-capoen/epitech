/*
** EPITECH PROJECT, 2024
** display.c
** File description:
** display all informations
*/

#include "include/mytop.h"

static int display_mib(void)
{
    mib_t *mib_mem = get_mem_info();
    mib_t *mib_swap = get_swap_info();

    if (!mib_mem || !mib_swap)
        return 0;
    mvprintw(3, 0, "MiB Mem :  %.1f total,  %.1f free,   "
        "%.1f used,   %.1f buff/cache", mib_mem->total,
        mib_mem->free, mib_mem->used, mib_mem->avail);
    mvprintw(4, 0, "MiB Swap:   %.1f total,    %.1f free, "
        "   %.1f used.   %.1f avail Mem", mib_swap->total,
        mib_swap->free, mib_swap->used, mib_swap->avail);
    free(mib_mem);
    free(mib_swap);
    return 0;
}

static void print_loadavg(void)
{
    float load_one = 0.00;
    float load_two = 0.00;
    float load_three = 0.00;
    int result = 0;
    FILE *fp = fopen("/proc/loadavg", "r");

    result = fscanf(fp, "%f %f %f", &load_one, &load_two, &load_three);
    if (result == 1)
        printw("%.2f\n", load_one);
    if (result == 2)
        printw("%.2f, %.2f\n", load_one, load_two);
    if (result == 3)
        printw("%.2f, %.2f, %.2f\n", load_one, load_two, load_three);
}

int display_header(cpu_time_t *prev)
{
    struct tm *time = get_time();
    cpu_t *cpu = get_cpu_pourcentage(prev);

    mvprintw(0, 0, "top - %02d:%02d:%02d up 00:00,"
        " 0 users,  load average: ", time->tm_hour,
        time->tm_min, time->tm_sec);
    print_loadavg();
    mvprintw(2, 0, "%%Cpu(s):  %.1f us,  %.1f sy,  %.1f ni, "
        "%.1f id,  %.1f wa,  %.1f hi,  %.1f si,  %.1f st", cpu->us,
        cpu->sy, cpu->ni, cpu->id, cpu->wa, cpu->hi, cpu->si, cpu->st);
    display_mib();
    attron(A_STANDOUT);
    mvprintw(6, 0, "PID USER    PR  NI   VIRT    RES     "
        "SHR S %%CPU %%MEM   TIME+ COMMAND ");
    attroff(A_STANDOUT);
    free(cpu);
}

static char *display_virt(char *virt_str)
{
    unsigned long virt_size = strtoul(virt_str, NULL, 10);
    char *result = malloc(50 * sizeof(char));
    double virt = 0;

    if (!result)
        return NULL;
    if (virt_size >= 1024 * 1024 * 1024) {
        virt = virt_size / (1024.0 * 1024.0 * 1024.0);
        snprintf(result, 50, "%.2fg", virt);
    } else
        snprintf(result, 50, "%lu", virt_size / 1024);
    return result;
}

static char *display_time(proc_t *proc)
{
    unsigned long total_seconds = proc->time / sysconf(_SC_CLK_TCK);
    unsigned long minutes = total_seconds / 60;
    unsigned long seconds = total_seconds % 60;
    unsigned long centiseconds = (proc->time %
        sysconf(_SC_CLK_TCK)) * 100 / sysconf(_SC_CLK_TCK);
    char *time = malloc(sizeof(char) * 11);

    if (!time)
        return NULL;
    snprintf(time, 12, " %lu:%02lu.%02lu", minutes, seconds, centiseconds);
    return time;
}

int display_procs(proc_t *procs, int line, char *user)
{
    int *states = get_states(procs);

    mvprintw(1, 0, "Tasks: %i total, %i running, %i sleeping,"
        " %i stopped, %i zombie", states[0],
        states[1], states[2], states[3], states[4]);
    for (int i = 0; i < line; i++)
        procs = procs->next;
    for (int i = 7; procs != NULL; i++) {
        if (strcmp(user, procs->username) == 0 || strcmp(user, "NONE") == 0) {
            mvprintw(i, 0, "%-4s %-4s   %-3s % 3s % 6s % 6lu % 5i  "
                "%c %3i %3i %s %s", procs->pid, procs->username,
                procs->pr, procs->ni, display_virt(procs->virt),
                get_res(my_getnbr(procs->pid)), 0, procs->state, 0, 0,
                display_time(procs), get_command_name(my_getnbr(procs->pid)));
        }
        procs = procs->next;
    }
    free(states);
    return 0;
}
