#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <errno.h> // so we can set errno
#include <string.h>

#include "counters.h"

#define INITIAL_SIZE (32)
#define SIZE_MULTIPLIER (2)

// multiple counter abstraction
struct counters {
    size_t n;
    unsigned long long *data;
};

// create an array of n counters, all initially 0
Counters 
countersCreate(void) {
    struct counters *c = malloc(sizeof(struct counters));
    assert(c);
    c->n = INITIAL_SIZE;
    c->data = calloc(c->n, sizeof(unsigned long long));

    return c;
}

// free all space used by counters
void
countersDestroy(Counters c)
{
    free(c->data);
    free(c);
}

// increment the i-th counter
void 
countersIncrement(Counters c, size_t i)
{
    if(i >= c->n) {
        // need to grow table
        size_t newSize = c->n * SIZE_MULTIPLIER;

        if(i >= newSize) {
            newSize = i+1;
        } 

        // grow data
        c->data = realloc(c->data, newSize * sizeof(unsigned long long));
        assert(c->data);

        // could use for loop to zero out new places
        // but will use memset instead
        memset(c->data + c->n, 0, (newSize - c->n) * sizeof(unsigned long long));

        c->n = newSize;
    }

    c->data[i]++;
}

// return the value of the i-th counter
unsigned long long 
countersValue(Counters c, size_t i)
{
    if(i < c->n) {
        return c->data[i];
    } else {
        return 0;
    }
}

// return number of counters in objects
size_t
countersSize(Counters c)
{
    return c->n;
}

// clone a Counters object
Counters 
countersClone(Counters c)
{
    Counters c2;

    c2 = malloc(sizeof(struct counters));

    c2->n = c->n;
    c2->data = calloc(c2->n, sizeof(unsigned long long));

    // copy data from old counters
    memcpy(c2->data, c->data, c->n * sizeof(unsigned long long));

    return c;
}

// write a Counters object to FILE *
// returns 1 on success, 0 on failure
// in case of failure, errno will be set
int 
countersWrite(Counters c, FILE *f)
{
    if(fwrite(&c->n, sizeof(size_t), 1, f) != 1
        || fwrite(c->data, sizeof(unsigned long long), c->n, f) != c->n) {
        return 0;
    } else {
        return 1;
    }
}

// read a Counters object from FILE *
// returns null pointer on failure
// in case of failure, errno will be set
Counters 
countersRead(FILE *f)
{
    Counters c = malloc(sizeof(struct counters));

    // read c->n
    if(fread(&c->n, sizeof(size_t), 1, f) != 1) {
        free(c);
        return 0;
    }

    c->data = calloc(c->n, sizeof(unsigned long long));
    assert(c->data);

    if(fread(c->data, sizeof(unsigned long long), c->n, f) != c->n) {
        countersDestroy(c);
        return 0;
    }

    return c;
}
