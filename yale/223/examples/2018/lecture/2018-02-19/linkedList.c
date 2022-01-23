#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct elt {
    struct elt *next;  // my successor in the linked list
    int value;         // stored value;
};

// make a new empty stack
struct elt *
stackCreate(void)
{
    return 0;
}

// push a value onto top of stack
// (i.e. insert at front of list)
// takes old list, returns new list
struct elt *
stackPush(struct elt *old, int value)
{
    struct elt *new;

    new = malloc(sizeof(struct elt));
    assert(new);

    new->next = old;
    new->value = value;

    return new;
}

// removes and returns top of nonempty stack
// returned value goes in *value
struct elt *
stackPop(struct elt *old, int *value)
{
    struct elt *new;

    assert(old != 0);

    new = old->next;
    *value = old->value;

    free(old);

    return new;
}

// returns true if stack is nonEmpty
int
stackNotEmpty(const struct elt *old)
{
    return old != 0;
}

// free up a stack
void
stackDestroy(struct elt *s)
{
    int value;

    while(stackNotEmpty(s)) {
        s = stackPop(s, &value);
    }
}

// print contents of stack
void
stackPrint(struct elt *s)
{
    while(s) {
        printf("%d ", s->value);
        s = s->next;
    }
}

// print contents of stack
void
stackPrintFriendly(struct elt *s)
{
    for(struct elt *s2 = s; s2; s2 = s2->next) {
        printf("%d ", s2->value);
    }
}

int
main(int argc, char **argv)
{
    struct elt *stack = stackCreate();
    int c;

    // load up the input in the stack
    while((c = getchar()) != EOF) {
        stack = stackPush(stack, c);
        // demo: print stack contents
        stackPrint(stack);
        putchar('\n');
    }

    // print out contents of stack in reverse order
    while(stackNotEmpty(stack)) {
        stack = stackPop(stack, &c);
        putchar(c);
    }

    stackDestroy(stack);

    return 0;
}
