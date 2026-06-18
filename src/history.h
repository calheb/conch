/*
 * history.h - command history for the conch shell
 *
 * Stores a dynamic array of command strings that doubles in capacity
 * when full.
 */

#ifndef HISTORY_H
#define HISTORY_H

/* holds all entered commands and the state of the dynamic array */
typedef struct {
    char **entries; /* array of command strings */
    int count;      /* number of entries currently stored */
    int capacity;   /* total slots allocated */
} History;

/* initialize h with the given starting capacity */
void history_init(History *h, int initial_capacity);

/* append a copy of cmd to h, doubling capacity if neeeded */
void history_add(History *h, const char *cmd);

/* print all stored commands, one per line, with a 1-based index */
void history_print(const History *h);

/* free all memory owned by h */
void history_free(History *h);

#endif /* HISTORY_H */
