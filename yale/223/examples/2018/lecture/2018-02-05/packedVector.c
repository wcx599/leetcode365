#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

struct vector {
    int length;
    int a[];     /* allocate no space for this array */
    /* only works in last position */
};

// allocate a new vector of size length
struct vector *
vectorCreate(int length)
{
    struct vector *v;

    v = malloc(sizeof(struct vector) + sizeof(int) * length);
    assert(v);

    v->length = length;

    return v;
}

void
vectorDestroy(struct vector *v)
{
    free(v);
}

void
vectorSet(struct vector *v, int index, int value)
{
    assert(index >= 0 && index < v->length);
    v->a[index] = value;
}

int
vectorGet(const struct vector *v, int index)
{
    assert(index >= 0 && index < v->length);
    return v->a[index];
}

void
printArray(int length, const int *a)
{
    for(int i = 0; i < length; i++) {
        printf("%d ", a[i]);
    }
    putchar('\n');

#ifdef EVIL
    // evil, don't do it
    int *aa;

    aa = (int *) a;  /* casting away const */
    aa[0] = 3417;
#endif
}

void
vectorPrint(const struct vector *v)
{
    printArray(v->length, v->a);
}

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
