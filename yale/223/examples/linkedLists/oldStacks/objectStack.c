#include <stdlib.h>
#include <string.h>

/* Imperative-style stack */
/* All operations modify the stack in place */

/* a Stack is a pointer to a pointer to the first element of a linked list */
typedef struct stack {
    char *book;         /* malloc'd name of book */
    struct stack *next; /* next item in stack, or 0 if there aren't any more */
} **Stack;

/* create a new empty stack */
Stack
stackCreate(void)
{
    Stack s;
    
    s = malloc(sizeof(struct stack *));
    *s = 0;

    return s;
}

/* push a new book on the stack */
/* copies second argument book (so you don't need to keep it around) */
/* returns 0 on allocation error or 1 on success */
int
stackPush(Stack s, const char *book)
{
    struct stack *new;

    new = malloc(sizeof(*new));

    new->next = *s;
    new->book = strdup(book);

    if(new->book == 0) {
        free(new);
        return 0;
    }

    *s = new;
    return 1;
}

/* pops a book off the stack */
/* returns 0 if stack is empty */
char *
stackPop(Stack s)
{
    struct stack *new;
    char *book;

    if(*s == 0) {
        return 0;
    } else {
        book = (*s)->book;

        /* we have to save (*s)->next before we free it */
        new = (*s)->next;
        free(*s);
        *s = new;
        return book;
    }
}

/* returns true if s is empty */
int
stackEmpty(Stack s)
{
    return (*s) == 0;
}

/* frees a stack */
void
stackDestroy(Stack s)
{
    while(!stackEmpty(s)) {
        free(stackPop(s));
    }

    free(s);
}
