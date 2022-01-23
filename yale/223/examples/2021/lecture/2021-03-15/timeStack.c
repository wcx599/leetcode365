#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "stack.h"

// do some basic stack tinkering

int
main(int argc, char **argv)
{

    if(argc != 2) {
        return 1;
    }

    int n = atoi(argv[1]);

    Stack s = stackCreate();

    for(int i = 0; i < n; i++) {
        stackPush(s, i);
    }

    while(!stackEmpty(s)) {
        stackPop(s);
    }

    for(int i = 0; i < n; i++) {
        stackPush(s, i);
    }

    stackDestroy(s);

    return 0;
}
