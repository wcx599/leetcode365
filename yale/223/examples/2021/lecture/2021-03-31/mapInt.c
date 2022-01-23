#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "mapInt.h"

struct mapInt {
    size_t m;    // number of locations in table
    size_t n;    // number of stored elements
    struct elt **table;   // table of linked lists
};

struct elt {
    struct elt *next;
    Key key;     // abstract key object
    int value;   // value being stored
};

#define INITIAL_SIZE (32)
#define SIZE_MULTIPLIER (2)

static MapInt 
mapIntCreateInternal(size_t initialSize)
{
    MapInt d = malloc(sizeof(struct mapInt));
    assert(d);

    d->m = initialSize;
    d->n = 0;
    d->table = calloc(d->m, sizeof(struct elt *));
    assert(d->table);

    return d;
}

MapInt 
mapIntCreate(void)
{
    return mapIntCreateInternal(INITIAL_SIZE);
}

void 
mapIntDestroy(MapInt d)
{
    // walk through all table entries and delete them
    struct elt *next;
    for(size_t i = 0; i < d->m; i++) {
        for(struct elt *e = d->table[i]; e != 0; e = next) {
            next = e->next;
            e->key->methods->destroy(e->key);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

// returns pointer to matching int location
// this may not remain valid after another
// call to mapIntLookup.
int *
mapIntLookup(MapInt d, Key k)
{
    // where to start looking
    size_t i = k->methods->hash(k) % d->m;

    // walk down linked list
    for(struct elt *e = d->table[i]; e != 0; e = e->next) {
        if(e->key->methods->isEqual(e->key, k)) {
            // found it
            return &e->value;
        }
    }

    // didn't find it
    // make a new elt, patch in
    struct elt *e = malloc(sizeof(struct elt));
    e->next = d->table[i];
    e->key = k->methods->copy(k);
    e->value = 0;

    d->table[i] = e;

    d->n++;

    if(d->n >= d->m) {
        // too full!
        // make a new table
        MapInt d2 = mapIntCreateInternal(d->m * SIZE_MULTIPLIER);

        // reinsert everything
        for(size_t i = 0; i < d->m; i++) {
            for(struct elt *e = d->table[i]; e != 0; e = e->next) {
                *mapIntLookup(d2, e->key) = e->value;
            }
        }

        // swap guts of d and d2
        struct mapInt temp;

        temp = *d;
        *d = *d2;
        *d2 = temp;

        // delete d2
        mapIntDestroy(d2);

        // look up key in the new structure
        return mapIntLookup(d, k);

    } else {

        // return elt we already found
        return &e->value;

    }
}

static void
printEntry(Key key, int *value, void *data)
{
    fprintf(data, "%d ", *value);
    key->methods->print(key, data);
    fprintf(data, "\n");
}

// print all pairs in table
void
mapIntPrint(MapInt d, FILE *f)
{
    mapIntForeach(d, printEntry, f);
}

// operate on all pairs in table
void
mapIntForeach(MapInt d, 
        void (*f)(Key, int *, void *),
        void *data)
{
    // walk through all table entries
    for(size_t i = 0; i < d->m; i++) {
        for(struct elt *e = d->table[i]; e != 0; e = e->next) {
            f(e->key, &e->value, data);
        }
    }
}
