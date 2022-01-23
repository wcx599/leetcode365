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
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    Stack s = stackCreate();

    for(int i = 0; i < n; i++) {
        printf("pushed %d\n", i);
        stackPush(s, i);
        stackPrint(s);
    }

    while(!stackEmpty(s)) {
        int v = stackPop(s);
        printf("popped %d\n", v);
        stackPrint(s);
    }

    for(int i = 0; i < n; i++) {
        printf("pushed %d\n", i);
        stackPush(s, i);
        stackPrint(s);
    }

    stackDestroy(s);

    return 0;
}
