#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "deque.h"

int
main(int argc, char **argv)
{

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    Deque d = dequeCreate();

    for(int i = 0; i < 10; i++) {
        dequeEnq(d, LEFT, i);
        dequeEnq(d, RIGHT, i);
    }

    while(!dequeIsEmpty(d)) {
        printf("%d\n", dequeDeq(d, LEFT));
    }

    // maybe later test dequeueing from RIGHT

    dequeDestroy(d);

    return 0;
}
