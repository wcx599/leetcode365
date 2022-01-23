#include <stdlib.h>
#include <assert.h>

#include "stack.h"

struct stack {
    struct block *head;
};

#define BLOCK_SIZE (1024)

struct block {
    struct block *next;
    int top;
    int values[BLOCK_SIZE];
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
    struct block *e;
    struct block *next;

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
    struct block *b;

    if(s->head == 0 || s->head->top == BLOCK_SIZE) {
        /* need a new block */
        b = malloc(sizeof(*b));
        assert(b);

        b->next = s->head;
        b->top = 0;
        s->head = b;
    }

    /* first block exists and is not full */
    s->head->values[s->head->top++] = v;
}

int
stackPop(Stack s)
{
    struct block *b;
    int ret;

    b = s->head;
    assert(b);

    ret = b->values[--(b->top)];

    if(b->top == 0) {
        /* free and remove */
        s->head = b->next;
        free(b);
    }

    return ret;
}
