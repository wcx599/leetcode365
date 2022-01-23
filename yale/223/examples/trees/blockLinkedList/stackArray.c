#include <stdlib.h>
#include <assert.h>

#include "stack.h"

struct stack {
    int size;      /* number of spaces in values */
    int top;       /* first unused space */
    int *values;        /* data */
};

#define INITIAL_SIZE (512)

Stack
stackCreate(void)
{
    Stack s;

    s = malloc(sizeof(*s));
    assert(s);

    s->size = INITIAL_SIZE;
    s->top = 0;
    s->values = malloc(sizeof(*s->values) * s->size);

    return s;
}

void
stackDestroy(Stack s)
{
    free(s->values);
    free(s);
}

int
stackIsEmpty(Stack s)
{
    return s->top == 0;
}

void
stackPush(Stack s, int v)
{
    if(s->top >= s->size) {
        s->size *= 2;
        s->values = realloc(s->values, sizeof(*s->values) * s->size);
        assert(s->values);
    }

    s->values[s->top++] = v;
}

int
stackPop(Stack s)
{
    assert(s->top > 0);
    return(s->values[--(s->top)]);
}
