#include <stdlib.h>
#include <string.h>

/* Functional-style stack */
/* All operations consume the old value and return the new value of the stack */

typedef struct stack {
    char *book;         /* malloc'd name of book */
    struct stack *next; /* next item in stack, or 0 if there aren't any more */
} *Stack;

#define EMPTY_STACK (0)

/* create a new empty stack */
Stack
stackCreate(void)
{
    return EMPTY_STACK;
}

/* push a new book on the stack */
/* copies second argument book (so you don't need to keep it around) */
/* returns 0 on allocation error */
Stack
stackPush(Stack old, const char *book)
{
    Stack new;

    new = malloc(sizeof(*new));
    if(new == 0) return 0;

    new->next = old;
    new->book = strdup(book);

    if(new->book == 0) {
        free(new);
        return 0;
    }

    return new;
}

/* pops a book off the stack */
/* returns new tail of stack, stores book in *book */
/* *book is malloc'd data that the caller should free */
/* Stores 0 in *book if stack is empty */
Stack
stackPop(Stack old, char **book /*RETVAL*/)
{
    Stack new;

    if(old == 0) {
        *book = 0;
        return 0;
    } else {
        new = old->next;
        *book = old->book;
        free(old);
        return new;
    }
}

/* frees a stack */
void
stackDestroy(Stack s)
{
    char *book;

    while(s) {
        s = stackPop(s, &book);
        free(book);
    }
}
