#ifndef _STACK_H
#define _STACK_H

#include "object.h"

// basic stack implementation
// stack is a pointer to its first element
// caller will keep a pointer to this
typedef struct elt *Stack;

// create and destroy stacks
Stack *stackCreate(void);
void stackDestroy(Stack *);

// usual functions
void stackPush(Stack *s, Object *);

// don't call this on an empty stack
Object *stackPop(Stack *s);

// returns true if not empty
int stackNotEmpty(const Stack *s);

// print the elements of a stack to stdout
// using function print
void stackPrint(const Stack *s);

#endif
