#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h> // not implemented

#include "stack.h"

struct stack {
    int *values;  // contents of stack
    size_t n;            // number of stored elements
    size_t size;         // size of values array
};

#define INITIAL_SIZE (32)

// make a new empty stack
Stack
stackCreate(void)
{
    Stack s = malloc(sizeof(struct stack));
    assert(s);

    s->size = INITIAL_SIZE;
    s->values = malloc(sizeof(int) * s->size);
    s->n = 0;

    return s;
}

// free all space used by s
void 
stackDestroy(Stack s) 
{
    free(s->values);
    free(s);
}

#define SIZE_MULTIPLIER (2)

// push a new value on top of the stack
void
stackPush(Stack s, int v)
{
    // make sure I have space
    if(s->n >= s->size) {
        s->size *= SIZE_MULTIPLIER;
        s->values = realloc(s->values, s->size * sizeof(int));
    }

    // fill it in
    s->values[s->n++] = v;
}

// returns 1 if stack is empty, 0 otherwise
int
stackEmpty(Stack s)
{
    return s->n == 0;
}

// pop top value from a nonempty stack
int
stackPop(Stack s)
{
    assert(!stackEmpty(s));

    return s->values[--(s->n)];
}

// print contents of stack, starting from top
void
stackPrint(Stack s)
{
    if(s->n > 0) {
        for(size_t i = s->n - 1; i > 0; i--) {
            printf("%d ", s->values[i]);
        }
        printf("%d", s->values[0]);
    }
    putchar('\n');
}
