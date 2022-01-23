#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define N (1<<24)

int
main(int argc, char **argv)
{
    int i;
    Stack s;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    s = stackCreate();

    for(i = 0; i < N; i++) {
        stackPush(s, i);
    }

    assert(!stackIsEmpty(s));

    for(i = N-1; i >= 0; i--) {
        assert(stackPop(s) == i);
    }

    assert(stackIsEmpty(s));

    stackDestroy(s);

    return 0;
}
