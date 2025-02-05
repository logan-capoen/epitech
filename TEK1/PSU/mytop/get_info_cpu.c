/*
** EPITECH PROJECT, 2024
** get_info_cpu
** File description:
** get info of the cpu
*/

#include "include/mytop.h"

int read_cpu_times(cpu_time_t *cpu)
{
    FILE *file = fopen("/proc/stat", "r");

    if (!file)
        return 84;
    fscanf(file, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
        &cpu->us, &cpu->ni, &cpu->sy, &cpu->id,
        &cpu->wa, &cpu->hi, &cpu->si, &cpu->st);
    fclose(file);
    return 0;
}

cpu_t *get_cpu_pourcentage(cpu_time_t *p)
{
    cpu_time_t c;
    unsigned long total_prev;
    unsigned long total_curr;
    unsigned long total;
    cpu_t *cpu = malloc(sizeof(cpu_t));

    read_cpu_times(&c);
    total_prev = p->hi + p->id + p->ni + p->si + p->st + p->sy + p->us + p->wa;
    total_curr = c.hi + c.id + c.ni + c.si + c.st + c.sy + c.us + c.wa;
    total = total_curr - total_prev;
    cpu->hi = (double)(c.hi - p->hi) / (double)total * 100;
    cpu->id = (double)(c.id - p->id) / (double)total * 100;
    cpu->ni = (double)(c.ni - p->ni) / (double)total * 100;
    cpu->si = (double)(c.si - p->si) / (double)total * 100;
    cpu->st = (double)(c.st - p->st) / (double)total * 100;
    cpu->sy = (double)(c.sy - p->sy) / (double)total * 100;
    cpu->us = (double)(c.us - p->us) / (double)total * 100;
    cpu->wa = (double)(c.wa - p->wa) / (double)total * 100;
    *p = c;
    return cpu;
}
