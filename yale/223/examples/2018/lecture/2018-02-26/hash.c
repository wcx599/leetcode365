#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "hash.h"
#include "stringutil.h"

// invariant: empty slots have null keys
struct elt {
    char *key;
    int value;
};

struct hash {
    size_t size;   // size of array
    size_t elts;   // how many elements
    struct elt *a; // actual table of elements
};

#define MULTIPLIER (2) // extra space to keep load factor down, see hashCreate

// create a hash table for storing up to n elts
Hash *
hashCreate(size_t n) {
    Hash *h = malloc(sizeof(struct hash));
    
    h->size = MULTIPLIER * n;  // start extra big because we don't reallocate
    h->elts = 0;

    h->a = calloc(h->size, sizeof(struct elt));

    return h;
}

void
hashDestroy(Hash *h)
{
    // need to free keys
    for(size_t i = 0; i < h->size; i++) {
        if(h->a[i].key != 0) {
            free(h->a[i].key);
        }
    }

    free(h->a);
    free(h);
}

// terrible hash function
size_t
hashFunction(const char *key)
{
    size_t h = 0;

    for(size_t i = 0; key[i] != '\0'; i++) {
        h = h * 97 + key[i];
    }

    return h;
}

// find position of key in h
// or first empty position if not in h
static size_t
hashFind(const Hash *h, const char *key)
{
    size_t hashed = hashFunction(key) % h->size;

    while(h->a[hashed].key != 0 && strcmp(h->a[hashed].key, key) != 0) {
        hashed = (hashed + 1) % h->size;
    }

    return hashed;
}

void
hashSet(Hash *h, const char *key, int value)
{
    // where should key go?
    size_t pos = hashFind(h, key);

    if(h->a[pos].key == 0) {
        // put in key
        h->a[pos].key = strSave(key);
        h->elts++;

        // If we were doing this right, we would grow
        // the hash table here if h->elts was too close
        // to h->size.
        //
        // Instead, we will just fail.
        assert(h->elts * MULTIPLIER <= h->size);
    }
    h->a[pos].value = value;
}

// if key is in h, put value in *value, return 1,
// else return 0
int 
hashGet(const Hash *h, const char *key, int *value)
{
    size_t pos = hashFind(h, key);

    if(h->a[pos].key == 0) {
        return 0;
    } else {
        *value = h->a[pos].value;

        return 1;
    }
}


// print contents of h
void
hashPrint(const Hash *h) {
    for(size_t i = 0; i < h->size; i++) {
        if(h->a[i].key != 0) {
            printf("%s %d\n", h->a[i].key, h->a[i].value);
        }
    }
}
