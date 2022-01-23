#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "dictStringInt.h"

struct dictStringInt {
    size_t m;    // number of locations in table
    size_t n;    // number of stored elements
    struct elt **table;   // table of linked lists
};

struct elt {
    struct elt *next;
    int value;   // value being stored
    char key[];  // null-terminated character string
};

#define INITIAL_SIZE (32)
#define SIZE_MULTIPLIER (2)

static DictStringInt 
dictStringIntCreateInternal(size_t initialSize)
{
    DictStringInt d = malloc(sizeof(struct dictStringInt));
    assert(d);

    d->m = initialSize;
    d->n = 0;
    d->table = calloc(d->m, sizeof(struct elt *));
    assert(d->table);

    return d;
}

DictStringInt 
dictStringIntCreate(void)
{
    return dictStringIntCreateInternal(INITIAL_SIZE);
}

void 
dictStringIntDestroy(DictStringInt d)
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

#define FNV_PRIME_64 ((1ULL<<40)+(1<<8)+0xb3)
#define FNV_OFFSET_BASIS_64 (14695981039346656037ULL)

uint64_t
FNV1a(const char *s)
{
    uint64_t h = FNV_OFFSET_BASIS_64;

    while(*s != '\0') {
        h ^= *s++;
        h *= FNV_PRIME_64;
    }

    return h;
}

// returns pointer to matching int location
// this may not remain valid after another
// call to dictStringIntLookup.
int *
dictStringIntLookup(DictStringInt d, const char *s)
{
    // where to start looking
    size_t i = FNV1a(s) % d->m;

    // walk down linked list
    for(struct elt *e = d->table[i]; e != 0; e = e->next) {
        if(!strcmp(e->key, s)) {
            // found it
            return &e->value;
        }
    }

    // didn't find it
    // make a new elt, patch in
    struct elt *e = malloc(sizeof(struct elt) + strlen(s) + 1);
    e->next = d->table[i];
    e->value = 0;
    strcpy(e->key, s);

    d->table[i] = e;

    d->n++;

    if(d->n >= d->m) {
        // too full!
        // make a new table
        DictStringInt d2 = dictStringIntCreateInternal(d->m * SIZE_MULTIPLIER);

        // reinsert everything
        for(size_t i = 0; i < d->m; i++) {
            for(struct elt *e = d->table[i]; e != 0; e = e->next) {
                *dictStringIntLookup(d2, e->key) = e->value;
            }
        }

        // swap guts of d and d2
        struct dictStringInt temp;

        temp = *d;
        *d = *d2;
        *d2 = temp;

        // delete d2
        dictStringIntDestroy(d2);

        // look up key in the new structure
        return dictStringIntLookup(d, s);

    } else {

        // return elt we already found
        return &e->value;

    }
}

// print all pairs in table
void
dictStringIntPrint(DictStringInt d, FILE *f)
{
    // walk through all table entries
    for(size_t i = 0; i < d->m; i++) {
        for(struct elt *e = d->table[i]; e != 0; e = e->next) {
            fprintf(f, "%d %s\n", e->value, e->key);
        }
    }
}
