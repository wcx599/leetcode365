#include <stdlib.h>
#include <assert.h>

#include "stack.h"

struct stack {
    struct elt *head;
};

struct elt {
    struct elt *next;
    int value;
};

Stack
stackCreate(void)
{
    Stack s;

    s = malloc(sizeof(*s));
    assert(s);

    s->head = 0;

    return s;
}

void
stackDestroy(Stack s)
{
    struct elt *e;
    struct elt *next;

    for(e = s->head; e; e = next) {
        next = e->next;
        free(e);
    }

    free(s);
}

int
stackIsEmpty(Stack s)
{
    return s->head == 0;
}

void
stackPush(Stack s, int v)
{
    struct elt *e;

    e = malloc(sizeof(*e));
    assert(e);

    e->value = v;
    e->next = s->head;
    s->head = e;
}

int
stackPop(Stack s)
{
    struct elt *e;
    int ret;

    e = s->head;
    assert(e);

    ret = e->value;
    s->head = e->next;

    free(e);

    return ret;
}


