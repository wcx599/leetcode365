#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "eval.h"

struct demo {
    char c;
    int i;
};

struct {
    int x;
    int y;
} GlobalPoint;

struct vector {
    int length;
    int *a;
};

// allocate a new vector of size length
struct vector *
vectorCreate(int length)
{
    struct vector *v;

    v = malloc(sizeof(struct vector));
    assert(v);

    v->length = length;
    v->a = malloc(sizeof(int) * length);

    assert(v->a);

    return v;
}

void
vectorDestroy(struct vector *v)
{
    free(v->a);
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


#define N (10)

int
main(int argc, char **argv)
{
    struct demo d;
    struct demo *p;  // p is a pointer to struct demo
    struct vector *v;

    d.c = 'x';
    d.i = 12;

    Eval(d.c);
    Eval(d.i);

    p = &d;

    Eval((*p).i);  // parens required to avoid bad issues
    Eval(p->i);    // replaces . and *

    v = vectorCreate(N);
    vectorSet(v, 8, 6);

    // C does not prevent this
    // v->a[v->length + 117] = -17;
    
    Eval(vectorGet(v, 8));

    vectorDestroy(v);

    return 0;
}
