#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "object.h"
#include "intObject.h"
#include "stringObject.h"

#include "stack.h"

#define N (3)

// do some stack stuff
int
main(int argc, char **argv)
{
    char str[] = "hi";
    Object *o;

    int n = N;
    if(argc >= 2) {
        n = atoi(argv[1]);
    }

    Stack *s = stackCreate();

    for(int i = 0; i < n; i++) {
        // push a string onto the stack
        str[0] = 'a' + i;
        o = stringObjectCreate(str);
        stackPush(s, o);
        o->methods->destroy(o);
        stackPrint(s);

        // push an int onto the stack
        o = intObjectCreate(i);
        stackPush(s, o);
        o->methods->destroy(o);
        stackPrint(s);
    }

    while(stackNotEmpty(s)) {
        o = stackPop(s);
        putchar('[');
        o->methods->print(o);
        o->methods->destroy(o);
        fputs("] ", stdout);
        stackPrint(s);
    }

    stackDestroy(s);

    return 0;
}
