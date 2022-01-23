#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "table.h"

// adapted from dictStringInt.c example from lecture

struct table {
    size_t m;    // number of locations in table
    size_t n;    // number of stored elements
    struct elt **table;   // table of linked lists
};

struct elt {
    struct elt *next;
    uint64_t hash;    // hash of password
    char password[];  // null-terminated character string
};

#define INITIAL_SIZE (32)
#define SIZE_MULTIPLIER (2)

static Table 
tableCreateInternal(size_t initialSize)
{
    Table d = malloc(sizeof(struct table));
    assert(d);

    d->m = initialSize;
    d->n = 0;
    d->table = calloc(d->m, sizeof(struct elt *));
    assert(d->table);

    return d;
}

Table 
tableCreate(void)
{
    return tableCreateInternal(INITIAL_SIZE);
}

void 
tableDestroy(Table d)
{
    // walk through all table entries and delete them
    struct elt *next;
    for(size_t i = 0; i < d->m; i++) {
        for(struct elt *e = d->table[i]; e != 0; e = next) {
            next = e->next;
            free(e);
        }
    }

    free(d->table);
    free(d);
}

// returns pointer to string with given hash
const char *
tableLookup(Table d, uint64_t hash)
{
    // where to start looking
    size_t i = hash % d->m;

    // walk down linked list
    for(struct elt *e = d->table[i]; e != 0; e = e->next) {
        if(e->hash == hash) {
            // found it
            return e->password;
        }
    }

    // didn't find it
    return 0;
}

// insert new hash/password pair
void
tableInsert(Table d, uint64_t hash, const char *password)
{
    size_t i = hash % d->m;

    // make a new elt, patch in
    struct elt *e = malloc(sizeof(struct elt) + strlen(password) + 1);
    e->next = d->table[i];
    e->hash = hash;
    strcpy(e->password, password);

    d->table[i] = e;

    d->n++;

    if(d->n >= d->m) {
        // too full!
        // make a new table
        Table d2 = tableCreateInternal(d->m * SIZE_MULTIPLIER);

        // reinsert everything
        for(size_t i = 0; i < d->m; i++) {
            for(struct elt *e = d->table[i]; e != 0; e = e->next) {
                tableInsert(d2, e->hash, e->password);
            }
        }

        // swap guts of d and d2
        struct table temp;

        temp = *d;
        *d = *d2;
        *d2 = temp;

        // delete d2
        tableDestroy(d2);
    }
}
