/*
 * history.c - dynamic command history implementation
 */

#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * history_init - set up h with an allocated array of initial_capacity slots
 */
void history_init(History *h, int initial_capacity)
{
    h->entries = malloc(initial_capacity * sizeof(char *));
    h->count = 0;
    h->capacity = initial_capacity;
}

/*
 * history_add - append a copy of cmd to h
 *
 * If the array is full, its capacity is doubled before inserting.
 */
void history_add(History *h, const char *cmd)
{
    /* double the backing array when we run out of room */
    if (h->count == h->capacity) {
        h->capacity *= 2;
        h->entries = realloc(h->entries, h->capacity * sizeof(char *));
    }
    /* allocate and copy cmd */
    h->entries[h->count] = malloc(strlen(cmd) + 1);
    strcpy(h->entries[h->count++], cmd);
}

/*
 * history_print - print each stored command with a 1-based index
 */
void history_print(const History *h)
{
    int i;
    for (i = 0; i < h->count; i++)
        printf("%d %s\n", i + 1, h->entries[i]);
}

/*
 * history_free - release all memory owned by h
 */
void history_free(History *h)
{
    int i;
    for (i = 0; i < h->count; i++)
        free(h->entries[i]);
    free(h->entries);
    h->count = 0;
    h->capacity = 0;
}
