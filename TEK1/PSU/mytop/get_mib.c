/*
** EPITECH PROJECT, 2024
** get_mib.c
** File description:
** get all info for mib mem and mib swap
*/

#include "include/mytop.h"

static void find_line_mem(mib_t **mib_mem, char *line)
{
    unsigned long buffers = 0;
    unsigned long cached = 0;
    unsigned long value = 0;

    if (strncmp(line, "MemTotal:", 9) == 0) {
        sscanf(line, "MemTotal: %lu kB", &value);
        (*mib_mem)->total = value / 1024.0;
    }
    if (strncmp(line, "MemFree:", 8) == 0) {
        sscanf(line, "MemFree: %lu kB", &value);
        (*mib_mem)->free = value / 1024.0;
    }
    if (strncmp(line, "Buffers:", 8) == 0)
        sscanf(line, "Buffers: %lu kB", &buffers);
    if (strncmp(line, "Cached:", 7) == 0) {
        sscanf(line, "Cached: %lu kB", &cached);
        (*mib_mem)->avail = buffers / 1024.0 + cached / 1024.0;
    }
    (*mib_mem)->used = (*mib_mem)->total;
}

mib_t *get_mem_info(void)
{
    FILE *file = fopen("/proc/meminfo", "r");
    mib_t *mib_mem = malloc(sizeof(mib_t));
    char line[256];
    unsigned long aimable = 0;
    unsigned long available = 0;

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        find_line_mem(&mib_mem, line);
        if (strncmp(line, "SReclaimable:", 13) == 0)
            sscanf(line, "SReclaimable: %lu kB", &aimable);
        if (strncmp(line, "MemAvailable:", 13) == 0)
            sscanf(line, "MemAvailable: %lu kB", &available);
    }
    mib_mem->avail += aimable / 1024;
    mib_mem->used -= available / 1024;
    fclose(file);
    return mib_mem;
}

static void find_line_swap(mib_t **mib_swap, char *line)
{
    unsigned long value = 0;

    if (strncmp(line, "SwapTotal:", 10) == 0) {
        sscanf(line, "SwapTotal: %lu kB", &value);
        (*mib_swap)->total = value / 1024.0;
    }
    if (strncmp(line, "SwapFree:", 9) == 0) {
        sscanf(line, "SwapFree: %lu kB", &value);
        (*mib_swap)->free = value / 1024.0;
    }
    if (strncmp(line, "MemAvailable", 12) == 0) {
        sscanf(line, "MemAvailable: %lu kB", &value);
        (*mib_swap)->avail = value / 1024.0;
    }
    (*mib_swap)->used = (*mib_swap)->total - (*mib_swap)->free;
}

mib_t *get_swap_info(void)
{
    FILE *file = fopen("/proc/meminfo", "r");
    mib_t *mib_swap = malloc(sizeof(mib_t));
    char line[256];

    if (!file)
        return NULL;
    while (fgets(line, sizeof(line), file)) {
        find_line_swap(&mib_swap, line);
    }
    fclose(file);
    return mib_swap;
}
