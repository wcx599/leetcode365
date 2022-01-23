#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h> // not implemented

#include "stack.h"

struct stack {
    struct elt *top;  // top element, or 0 if empty
};

// basic linked list element
struct elt {
    struct elt *next;  // next element in list, or 0 at end of list
    int value;         // stored value
};

// make a new empty stack
Stack
stackCreate(void)
{
    Stack s = malloc(sizeof(struct stack));
    assert(s);

    s->top = 0;

    return s;
}

// free all space used by s
void 
stackDestroy(Stack s) 
{
    // empty s first
    while(!stackEmpty(s)) {
        stackPop(s);
    }

    // then free it
    free(s);
}

// push a new value on top of the stack
void
stackPush(Stack s, int v)
{
    // create a new stack element
    struct elt *e = malloc(sizeof(struct elt));
    assert(e);

    // fill it in
    e->value = v;
    e->next = s->top;

    // add to top
    s->top = e;
}

// returns 1 if stack is empty, 0 otherwise
int
stackEmpty(Stack s)
{
    return s->top == 0;
}

// pop top value from a nonempty stack
int
stackPop(Stack s)
{
    assert(!stackEmpty(s));

    // idea: remove and free top element
    // but I have to save s->top and s->top->value
    struct elt *e = s->top;
    int value = e->value;

    // move s->top to second element
    s->top = e->next;

    // free former top element
    free(e);

    // return value
    return value;
}

// print contents of stack, starting from top
void
stackPrint(Stack s)
{
    for(struct elt *e = s->top; e != 0; e = e->next) {
        printf("%d ", e->value);
    }
    putchar('\n');
}
