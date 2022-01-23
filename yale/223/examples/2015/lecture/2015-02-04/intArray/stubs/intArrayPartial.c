/* Implementation of IntArray ADT */

#include <stdlib.h>
#include <assert.h>

#include "intArray.h"

/* This definition is only visible in this file. */
struct intArray {
    size_t n;      /* number of elements */
    int *contents; /* malloc'd pointer contents */
};


IntArray *
intArrayCreate(size_t n, int defaultValue)
{
    IntArray *s;
    int i;

    s = malloc(sizeof(IntArray));
    if(s == 0) { return 0; }

    s->n = n;
    s->contents = malloc(sizeof(int) * n);

    if(s->contents == 0) {
        free(s);
        return 0;
    }

    for(i = 0; i < n; i++) {
        s->contents[i] = defaultValue;
    }

    return s;
}

size_t
intArraySize(const IntArray *a)
{
    /* STUB */
    return 0;
}

void
intArrayDestroy(IntArray *a)
{
    /* STUB */
}

int
intArrayGet(const IntArray *a, size_t index)
{
    /* STUB */
    return 0;
}

void 
intArraySet(IntArray *a, size_t index, int value)
{
    /*STUB*/
    ;
}
