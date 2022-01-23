#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define N (10)

int
main(int argc, char **argv)
{
    Q * q = qCreate();

    for(int i=0; i < N; i++) {
        enq(q, i);
    }

    while(!qEmpty(q)) { printf("%d\n", deq(q)); }

    qDestroy(q);

    return 0;
}
