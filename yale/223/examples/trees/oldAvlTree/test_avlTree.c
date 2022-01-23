#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avlTree.h"

#define N (1024)
#define MULTIPLIER (97)

int
main(int argc, char **argv)
{
    AvlTree t = AVL_EMPTY;
    int i;

    if(argc != 1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    for(i = 0; i < N; i++) {
        avlInsert(&t, (i*MULTIPLIER) % N);
    }

    printf("height %d\n", avlGetHeight(t));

    assert(avlSearch(t, N-1) == 1);
    assert(avlSearch(t, N) == 0);

    avlSanityCheck(t);

    for(i = 0; i < N-1; i++) {
        avlDeleteMin(&t);
    }

    avlSanityCheck(t);

    avlPrintKeys(t);

    avlDestroy(t);

    return 0;
}
