/*
** EPITECH PROJECT, 2024
** get_state
** File description:
** get the state of the procs
*/

#include "mytop.h"

static void add_state(proc_t *procs, int **states)
{
    if (procs->state == 'R')
        (*states)[1] += 1;
    if (procs->state != 'R' &&
        procs->state != 'T' && procs->state != 'Z')
        (*states)[2] += 1;
    if (procs->state == 'T')
        (*states)[3] += 1;
    if (procs->state == 'Z')
        (*states)[4] += 1;
    (*states)[0] += 1;
}

int *get_states(proc_t *procs)
{
    int *states = malloc(sizeof(int) * 5);

    states[0] = 0;
    states[1] = 0;
    states[2] = 0;
    states[3] = 0;
    states[4] = 0;
    while (procs != NULL) {
        add_state(procs, &states);
        procs = procs->next;
    }
    return states;
}
