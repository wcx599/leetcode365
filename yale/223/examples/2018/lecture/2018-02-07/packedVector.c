#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "packedVector.h"

/* implementation of a bounds-checked array */
struct vector {
    size_t length;  /* number of elements in the array */
    int a[];     /* allocate no space for this array */
    /* only works in last position */
};

// allocate a new vector of size length
struct vector *
vectorCreate(size_t length)
{
    struct vector *v;

    v = malloc(sizeof(struct vector) + sizeof(int) * length);
    assert(v);

    v->length = length;

    /* set all values to 0 */
    for(int i = 0; i < length; i++) {
        v->a[i] = 0;
    }

    return v;
}

void
vectorDestroy(struct vector *v)
{
    free(v);
}

void
vectorSet(struct vector *v, size_t index, int value)
{
    assert(index >= 0 && index < v->length);
    v->a[index] = value;
}

int
vectorGet(const struct vector *v, size_t index)
{
    assert(index >= 0 && index < v->length);
    return v->a[index];
}

static void
printArray(size_t length, const int *a)
{
    for(size_t i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');
}

void
vectorPrint(const struct vector *v)
{
    printArray(v->length, v->a);
}

#ifdef TEST_MAIN

/* only included if TEST_MAIN is defined */

#include "eval.h"

#define N (10)

int
main(int argc, char **argv)
{
    struct vector *v;

    v = vectorCreate(N);
    vectorSet(v, 8, 6);
    
    Eval(vectorGet(v, 8));

    /* violates abstract barrier! */
    printArray(v->length, v->a);
    printArray(v->length-2, v->a+2);

    /* preserves abstraction barrier */
    vectorPrint(v);

    vectorDestroy(v);

    return 0;
}

#endif
