#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

struct elt {
    struct elt *next;
    struct object *value;
};

// create and destroy stacks
Stack *
stackCreate(void) {
    Stack *s;

    s = malloc(sizeof(Stack));
    assert(s);
    *s = 0;  // empty stack
    return s;
}

void
stackDestroy(Stack *s) {
    struct object *o;
    while(stackNotEmpty(s)) {
        o = stackPop(s);
        o->methods->destroy(o);
    }
    free(s);
}

// usual functions
void 
stackPush(Stack *s, struct object *value) {
    struct elt *e = malloc(sizeof(struct elt));
    e->next = *s;
    e->value = value->methods->clone(value);
    *s = e;
}

// don't call this on an empty stack
struct object *
stackPop(Stack *s) {
    assert(stackNotEmpty(s));

    struct elt *e = *s;
    struct object *ret = e->value;

    *s = e->next;
    free(e);

    return ret;
}

// returns true if not empty
int
stackNotEmpty(const Stack *s) {
    return *s != 0;
}

// print the elements of a stack to stdout
void
stackPrint(const Stack *s) {
    for(struct elt *e = *s; e; e = e->next) {
        e->value->methods->print(e->value);
        putchar(' ');
    }
    putchar('\n');
}
